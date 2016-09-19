#pragma once

#include "graph.h"
#include <boost/algorithm/string.hpp>
#include <forward_list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class SymbolGraph {
public:
    using string = std::string;
    SymbolGraph() = default;
    SymbolGraph(const std::vector<std::vector<string>> &symbols) {
        for (const auto &row : symbols) {
            for (const auto &symbol : row)
                if (!contains(symbol))
                    symbol_to_id_.emplace(symbol, vertex_count_++);
        }

        id_to_symbol_.assign(vertex_count(), "");
        for (const auto &pair : symbol_to_id_)
            id_to_symbol_[pair.second] = pair.first;

        graph_.assign(vertex_count());
        for (const auto &row : symbols) {
            auto v = row.front();
            for (size_t i = 1; i < row.size(); ++i)
                add_edge(v, row[i]);
        }
    }

    void add_edge(const string &v, const string &w) {
        graph_.add_edge(symbol_to_id_[v], symbol_to_id_[w]);
    }

    size_t vertex_count() const { return vertex_count_; }

    size_t edge_count() const { return graph_.edge_count(); }

    size_t id_of(const string &symbol) const {
        return symbol_to_id_.at(symbol);
    }

    string symbol_of(size_t id) const { return id_to_symbol_.at(id); }

    bool contains(const string &symbol) const {
        return symbol_to_id_.find(symbol) != symbol_to_id_.end();
    }

    const Graph::AdjacentList & adjacent(const string& symbol) const {
        return graph_.adjacent(id_of(symbol));
    }

    string to_string() const {
        std::ostringstream os;
        os << "vertex count: " << vertex_count() << std::endl
           << "edge count: " << edge_count() << std::endl;
        for (size_t v = 0; v < graph_.vertex_count(); ++v) {
            os << symbol_of(v) << ":" << std::endl;
            for (auto w : graph_.adjacent(v))
                os << "\t" << symbol_of(w) << std::endl;
        }
        return os.str();
    }

    const Graph &graph() const { return graph_; }

private:
    std::unordered_map<string, size_t> symbol_to_id_;
    std::vector<string> id_to_symbol_;
    size_t vertex_count_ = 0;
    Graph graph_;
};

SymbolGraph create_symbol_graph(std::istream &is, const std::string &delim) {
    if (!is) {
        std::cerr << "bad istream" << std::endl;
        return SymbolGraph();
    }
    std::vector<std::vector<std::string>> symbols;
    for (std::string line; std::getline(is, line);) {
        symbols.emplace_back();
        boost::split(symbols.back(), line, boost::is_any_of(delim),
                     boost::token_compress_on);
    }
    return SymbolGraph(symbols);
}

SymbolGraph create_symbol_graph(const std::string &file_name,
                                const std::string delim) {
    std::ifstream is(file_name);
    return create_symbol_graph(is, delim);
}
