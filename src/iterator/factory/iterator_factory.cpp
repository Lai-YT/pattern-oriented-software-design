#include "iterator_factory.h"

#include <list>
#include <memory>
#include <mutex>
#include <string>

#include "../../shape.h"
#include "../iterator.h"
#include "../null_iterator.h"
#include "bfs_iterator_factory.h"
#include "dfs_iterator_factory.h"
#include "list_iterator_factory.h"

Iterator* IteratorFactory::createIterator() const {
  return new NullIterator{};
}

Iterator* IteratorFactory::createIterator(
    const std::list<Shape*>::const_iterator& begin,
    const std::list<Shape*>::const_iterator& end) const {
  return new NullIterator{};
}

std::unordered_map<std::string, std::unique_ptr<IteratorFactory>>
    IteratorFactory::pool_{};

IteratorFactory* IteratorFactory::getInstance(const std::string& type) {
  static std::mutex instance_mutex{};
  std::lock_guard<std::mutex> lock{instance_mutex};

  if (HasInstanceOf_(type)) {
    return pool_.at(type).get();
  }

  IteratorFactory* instance = nullptr;
  if (type == "BFS") {
    instance = new BFSIteratorFactory{};
  } else if (type == "DFS") {
    instance = new DFSIteratorFactory{};
  } else if (type == "List") {
    instance = new ListIteratorFactory{};
  } else {
    throw;
  }
  pool_.emplace(type, instance);
  return instance;
}

bool IteratorFactory::HasInstanceOf_(const std::string& type) {
  return pool_.find(type) != pool_.cend();
}
