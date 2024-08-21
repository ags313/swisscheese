#include "Output.h"
#include <chrono>
#include <format>

void SwissMeter::Output::start(const std::string & p_name) {
    auto const now = std::chrono::system_clock::now();
    auto const gmt = std::chrono::locate_zone("Etc/GMT");
    const std::chrono::zoned_time zoned_time{ gmt, floor<std::chrono::milliseconds>(now) };
    auto const filename = std::format("{}.{:%FT_%H%M%S}.timings.tsv", p_name, zoned_time);
    auto path = directory_ / filename;
    std::ostringstream buffer;

    for (int i = 0; i < columns_.size(); ++i) {
        if (i != 0) {
            buffer << "\t"; // Append a tab between columns, except before the first one
        }
        buffer << columns_[i];
    }
    output_ = new std::ofstream(path, std::ios::out | std::ios::app);
    *output_ << buffer.str() << std::endl;
}

void SwissMeter::Output::emit(const SingleMeasure *p_measure) {
    std::ostringstream buffer;
    buffer << p_measure->counter_ << SEPARATOR << p_measure->getEpochSeconds() << SEPARATOR;
    auto measures = p_measure->getMeasures();

    for (size_t i = 0; i < measures.size(); ++i) {
        if (i != 0) {
            buffer << "\t";
        }
        buffer << measures[i];
    }
    *output_ << buffer.str() << std::endl;
}

void SwissMeter::Output::end() {
    if(output_ == nullptr) {
        return;
    }
    output_->flush();
    output_->close();
    output_ = nullptr;
}
