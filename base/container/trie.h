// NOT thread safe

#pragma once

#include <algorithm>
#include <list>
#include <map>
#include <vector>
#include "common/file.h"
#include "container/dummy_map.h"

namespace base {

template<typename CharType, typename ValueType>
class Trie {
public:
	Trie() {
		nodes_.push_back(Node());  // root
	}

	void clear() {
		nodes_.clear();
		nodes_.push_back(Node());
	}

	size_t nodes_count() const {
		return nodes_.size();
	}

	bool insert(const std::vector<CharType>& str, const ValueType& value) {
		ChildMapIterator child_iter;
		size_t node_offset = 0;
		for (auto it = str.begin(); it != str.end(); ++it) {
			const CharType& current_char = *it;
			Node& node = nodes_[node_offset];
			if (node.get_child(current_char, &child_iter)) {
				node_offset = child_iter->second;
			} else {
				size_t new_child_offset = nodes_.size();
				node.child_map[current_char] = new_child_offset;
				node_offset = new_child_offset;
				nodes_.push_back(Node());
			}
		}

		push_value(value, &nodes_[node_offset]);
		return true;
	}

	bool insert(const std::vector<CharType>& str, const std::vector<ValueType>& values) {
		ChildMapIterator child_iter;
		size_t node_offset = 0;
		for (auto it = str.begin(); it != str.end(); ++it) {
			const CharType& current_char = *it;
			Node& node = nodes_[node_offset];
			if (node.get_child(current_char, &child_iter)) {
				node_offset = child_iter->second;
			} else {
				size_t new_child_offset = nodes_.size();
				node.child_map[current_char] = new_child_offset;
				node_offset = new_child_offset;
				nodes_.push_back(Node());
			}
		}

		Node& end_node = nodes_[node_offset];
		std::copy(values.begin(), values.end(), std::back_inserter(end_node.values));
		return true;
	}

	bool modify(const std::vector<CharType>& str, const ValueType& value) {
		size_t node_offset;
		if (!get_node(str, &node_offset)) {
			return false;
		}
		Node& end_node = nodes_[node_offset];
		auto value_iter = std::find(end_node.values.begin(), end_node.values.end(), value);
		if (value_iter == end_node.values.end()) {
			return false;
		}
		*value_iter = value;
		return true;
	}

	// Just erase value but not node. So this implement may cause redundant nodes.
	// The redundant nodes would be removed when reloading the trie.
	bool erase(const std::vector<CharType>& str, const ValueType& value) {
		size_t node_offset;
		if (!get_node(str, &node_offset)) {
			return false;
		}
		Node& end_node = nodes_[node_offset];
		auto value_iter = std::find(end_node.values.begin(), end_node.values.end(), value);
		if (value_iter == end_node.values.end()) {
			return false;
		}
		end_node.values.erase(value_iter);
		return true;
	}

	bool get_values(const std::vector<CharType>& str, std::vector<ValueType>* values) const {
		size_t node_offset;
		if (!get_node(str, &node_offset)) {
			return false;
		}
		const Node& end_node = nodes_[node_offset];
		if (end_node.values.empty()) {
			return false;
		}
		values->assign(end_node.values.begin(), end_node.values.end());
		return true;
	}

	// return [(offset, values), (offset, values), ...]
	std::vector<std::pair<size_t, std::vector<ValueType>>> search_substr(const std::vector<CharType>& str,
																		 bool english_style = false) const {
		std::vector<std::pair<size_t, std::vector<ValueType>>> result;
		ChildMapIterator child_iter;
		if (english_style) {
			for (size_t i = 0; i < str.size(); ++i) {
				if (i > 0 && is_alpha(str[i]) && is_alpha(str[i - 1])) {
					continue;
				}

				size_t node_offset = 0;
				std::vector<ValueType> tmp_values;
				int end = -1;
				for (size_t j = i; j < str.size(); ++j) {
					if (!nodes_[node_offset].get_child(str[j], &child_iter)) {
						break;
					}
					node_offset = child_iter->second;
					const Node& node = nodes_[node_offset];

					if (!node.values.empty()) {
						tmp_values = node.values;
						end = j;
					}
				}
				if (end != -1) {
					if (is_alpha(str[i]) && end + 1 < (int)str.size() && is_alpha(str[end + 1])) {
						continue;
					}

					result.push_back(std::make_pair(i, tmp_values));
					i = end;
				}
			}
		} else {
			for (size_t i = 0; i < str.size(); ++i) {
				size_t node_offset = 0;
				for (size_t j = i; j < str.size(); ++j) {
					if (!nodes_[node_offset].get_child(str[j], &child_iter)) {
						break;
					}
					node_offset = child_iter->second;
					const Node& node = nodes_[node_offset];
					if (!node.values.empty()) {
						result.push_back(std::make_pair(i, node.values));
					}
				}
			}
		}
		return result;
	}

	// Can ONLY dump c-style values.
	bool dump(const std::string& filename) const {
		std::string buffer = "*";
		std::vector<CharType> stack;
		serialize(nodes_[0], &stack, &buffer);
		return base::write_string_to_file(buffer, filename);
	}

	bool load(const std::string& filename) {
		clear();
		std::string buffer;
		if (!base::read_file_to_string(filename, &buffer)) {
			return false;
		}
		if (buffer.empty() || buffer[0] != '*') {
			return false;
		}
		for (size_t i = 1; i < buffer.size(); ) {
			// 1. key size (24 bit)
			int key_size = (int)buffer[i] | ((int)buffer[i + 1] << 8) | ((int)buffer[i + 2] << 16);
			i += 3;

			// 2. key
			std::vector<CharType> key((CharType*)&buffer[i], (CharType*)&buffer[i] + key_size);
			i += key_size * sizeof(CharType);

			// 3. value size (24 bit)
			int value_size = (int)buffer[i] | ((int)buffer[i + 1] << 8) | ((int)buffer[i + 2] << 16);
			i += 3;

			// 4. value
			std::vector<ValueType> values((ValueType*)&buffer[i], (ValueType*)&buffer[i] + value_size);
			i += value_size * sizeof(ValueType);

			if (!insert(key, values)) {
				return false;
			}
		}
		return true;
	}

private:
	//typedef std::map<CharType, size_t> ChildMap;
	typedef base::DummyMap<CharType, size_t> ChildMap;
	typedef typename ChildMap::const_iterator ChildMapIterator;

	struct Node {
		ChildMap child_map;
		std::vector<ValueType> values;

		bool get_child(const CharType& ch, ChildMapIterator* iter) const {
			*iter = child_map.find(ch);
			return *iter != child_map.end();
		}
	};

	bool get_node(const std::vector<CharType>& str, size_t* offset) const {
		ChildMapIterator child_iter;
		size_t& node_offset = *offset;
		node_offset = 0;
		for (auto it = str.begin(); it != str.end(); ++it) {
			if (!nodes_[node_offset].get_child(*it, &child_iter)) {
				return false;
			}
			node_offset = child_iter->second;
		}
		return true;
	}

	// 24 bit
	std::string size_to_string(size_t size) const {
		std::string size_buffer(3, '-');
		size_buffer[0] = (char)(size & 0xFF);
		size_buffer[1] = (char)((size >> 8) & 0xFF);
		size_buffer[2] = (char)((size >> 16) & 0xFF);
		return size_buffer;
	}

	void serialize(const Node& node, std::vector<CharType>* stack, std::string* buffer) const {
		const ChildMap& child_map = node.child_map;
		if (!node.values.empty()) {
			// 1. key size (24 bit)
			std::string key_size_buffer = size_to_string(stack->size());
			buffer->append(key_size_buffer);

			// 2. key
			buffer->append((const char*)&*stack->begin(), sizeof(CharType) * stack->size());

			// 3. values size (24 bit)
			std::string values_size_buffer = size_to_string(node.values.size());
			buffer->append(values_size_buffer);
			
			// 4. values
			buffer->append((const char*)&*node.values.begin(), sizeof(ValueType) * node.values.size());
		}

		for (auto it = child_map.begin(); it != child_map.end(); ++it) {
			stack->push_back(it->first);
			serialize(nodes_[it->second], stack, buffer);
			stack->pop_back();
		}
	}

	bool is_alpha(const CharType& ch) const {
		return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
	}	

	void push_value(const ValueType& value, Node* node) {
		auto& values = node->values;
		if (std::find(values.begin(), values.end(), value) == values.end()) {
			values.push_back(value);
		}
	}

	std::vector<Node> nodes_;
};

}  // namespace base
