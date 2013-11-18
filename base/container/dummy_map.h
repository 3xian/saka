// less memory, slower insert

#pragma once

#include <vector>
#include "common/macro.h"

namespace base {

template<typename Key, typename Value>
class DummyMap {
public:
	typedef std::pair<Key, Value> Node;
	typedef typename std::vector<Node>::iterator iterator;
	typedef typename std::vector<Node>::const_iterator const_iterator;

	void clear() {
		nodes_.clear();
	}

	const_iterator find(const Key& key) const {
		const_iterator it = std::lower_bound(nodes_.begin(), nodes_.end(), Node(key, Value()));
		if (it != nodes_.end() && it->first == key) {
			return it;
		} else {
			return nodes_.end();
		}
	}

	const_iterator end() const {
		return nodes_.end();
	}

	Value& operator [](const Key& key) {
		Node newcome(key, Value());
		auto it = std::lower_bound(nodes_.begin(), nodes_.end(), newcome);
		if (it == nodes_.end() || it->first != key) {
			it = nodes_.insert(it, newcome);
		}
		return it->second;
	}

private:
	std::vector<Node> nodes_;
};

}  // namespace base
