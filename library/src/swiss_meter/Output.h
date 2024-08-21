#pragma once

#include <string>
#include <filesystem>
#include <fstream>

#include "SingleMeasure.h"

namespace SwissMeter {
    class Output {
    public:
        explicit Output(const std::string &p_path,
                        const std::vector<std::string> &p_columns): directory_(p_path), columns_(p_columns) {
            try {
                std::filesystem::create_directories(p_path);
            } catch (const std::exception &e) {
                // do nothing
            }
        }

        void start(const std::string & p_name);

        void emit(const SingleMeasure * p_measure);

        void end();

    private:
        const std::string SEPARATOR = "\t";
        const std::filesystem::path directory_;
        std::ofstream *output_ = nullptr;
        std::vector<std::string> columns_;
    };
}
