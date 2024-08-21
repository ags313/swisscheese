#pragma once

#include <array>
#include <chrono>

namespace SwissMeter {
    struct SwitchFiles {
        std::string m_name;

        SwitchFiles() = default;

        ~SwitchFiles() = default;

        explicit SwitchFiles(const std::string &name): m_name(name) {
        };
    };

    struct SingleMeasure {
    public:
        SingleMeasure();

        SingleMeasure(long p_counter);

        ~SingleMeasure() {
        };

        SingleMeasure(const SingleMeasure &other)
            : counter_(other.counter_),
              measures_(other.measures_),
              whenSystem_(other.whenSystem_),
              whenHighRes_(other.whenHighRes_) {
        }

        SingleMeasure(SingleMeasure &&other) noexcept
            : counter_(other.counter_),
              measures_(other.measures_),
              whenHighRes_(other.whenHighRes_),
              whenSystem_(other.whenSystem_) {
        }

        SingleMeasure &operator=(const SingleMeasure &other) {
            if (this == &other)
                return *this;
            counter_ = other.counter_;
            measures_ = other.measures_;
            whenHighRes_ = other.whenHighRes_;
            whenSystem_ = other.whenSystem_;
            return *this;
        }

        SingleMeasure &operator=(SingleMeasure &&other) noexcept {
            if (this == &other)
                return *this;
            counter_ = other.counter_;
            measures_ = other.measures_;
            whenHighRes_ = other.whenHighRes_;
            whenSystem_ = other.whenSystem_;
            return *this;
        }

        void observeSinceStart(int column);

        void observeRaw(int column, long long value);

        void start(int column);

        void finish(int column);

        [[nodiscard]] long long getEpochSeconds() const;

        [[nodiscard]] std::array<long long, 8> getMeasures() const;

        long counter_;

    private:
        std::array<long long, 8> measures_;
        std::chrono::time_point<std::chrono::system_clock> whenSystem_;
        std::chrono::time_point<std::chrono::high_resolution_clock> whenHighRes_;
    };
}
