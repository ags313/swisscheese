#pragma once
#include <set>
#include <string>
#include <thread>
#include <variant>
#include <vector>

#include "MeasurementSession.h"
#include "Output.h"
#include "SingleMeasure.h"

#include "../../../cmake-build-debug/_deps/readerwriterqueue-src/atomicops.h"
#include "../../../cmake-build-debug/_deps/readerwriterqueue-src/readerwriterqueue.h"

using Message = std::variant<SwissMeter::SwitchFiles, SwissMeter::SingleMeasure>;

namespace SwissMeter {
    class MeasurementApi {
    public:
        MeasurementApi(): q_(moodycamel::ReaderWriterQueue<Message>(1024)),
                          currentMeasure_(new SingleMeasure(-1)),
                          writerThread_(std::jthread([this]() {
                                      Output output(this->directory_, columns_);
                                      while (shouldRun_) {
                                          Message * msg = nullptr;
                                          if ((msg = q_.peek()) != nullptr) {
                                              if (auto measure = std::get_if<SingleMeasure>(msg)) {
                                                  if (measure->counter_ >= 0) {
                                                      output.emit(measure);
                                                  }
                                              }
                                              if (auto instruction = std::get_if<SwitchFiles>(msg)) {
                                                  output.end();
                                                  output.start(instruction->m_name);
                                              }

                                              q_.pop();
                                          };
                                      };
                                  }

                              )
                          ) {
            columns_.emplace_back("frameNum");
            uniqueColumns_.insert("frameNum");
            columns_.emplace_back("frameEpoch");
            uniqueColumns_.insert("frameEpoch");
            for (int i = 0; i < 8; i++) {
                columns_.emplace_back(std::format("undefined{}", i));
            }
        };

        void setMeasurementDirectory(const std::string &path);

        void nameEvent(const std::string &name);

        void startMeasurementStream(const std::string &name);

        std::string getNameAtIdx(int i);

        void startObservation();

        void endObservation();

        void start(int column);

        void finish(int column);

        void observeSinceStart(int column);

        void observerRawValue(int column, long long value);

        void shutdown();

    private:
        std::set<std::string> uniqueColumns_;
        std::vector<std::string> columns_;
        std::string name_ = std::string{"none"};

        long counter_ = 0;
        MeasurementSession * currentRun_ = new MeasurementSession{name_, std::vector<std::string>{}};
        SingleMeasure * currentMeasure_;
        std::string directory_;

        moodycamel::ReaderWriterQueue<Message> q_;
        std::jthread writerThread_;
        std::atomic<bool> shouldRun_ = true;
    };
}
