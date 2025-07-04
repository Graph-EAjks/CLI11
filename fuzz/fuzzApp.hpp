// Copyright (c) 2017-2025, University of Cincinnati, developed by Henry Schreiner
// under NSF AWARD 1414736 and by the respective contributors.
// All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#ifdef CLI11_SINGLE_FILE
#include "CLI11.hpp"
#else
#include "CLI/CLI.hpp"
#endif

#include <atomic>
#include <complex>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace CLI {

class intWrapper64 {
  public:
    intWrapper64() = default;
    explicit intWrapper64(int64_t v) : val(v) {};
    CLI11_NODISCARD int64_t value() const { return val; }

  private:
    int64_t val{0};
};

class doubleWrapper {
  public:
    doubleWrapper() = default;
    explicit doubleWrapper(double v) : val(v) {};
    CLI11_NODISCARD double value() const { return val; }

  private:
    double val{0.0};
};

class stringWrapper {
  public:
    stringWrapper() = default;
    explicit stringWrapper(std::string_view v) : val(v) {};
    CLI11_NODISCARD std::string value() const { return val; }

  private:
    std::string val{};
};

/// @brief  class for extracting data for custom subcommand generation.
class SubcommandData {
  public:
    std::string name{""};
    std::string description{""};
    std::string modifiers{""};
    std::string data{""};
    std::size_t next{std::string::npos};
};

SubcommandData extract_subcomand_info(const std::string &description_string, std::size_t index);

class FuzzApp {
  public:
    FuzzApp() = default;
    /** generate a fuzzing application with a bunch of different interfaces*/
    std::shared_ptr<CLI::App> generateApp();
    /** compare two fuzz apps for equality*/
    CLI11_NODISCARD bool compare(const FuzzApp &other, bool print_error = false) const;
    /** generate additional options based on a string config*/
    std::size_t add_custom_options(CLI::App *app, const std::string &description_string);
    /** modify an option based on string*/
    static void modify_option(CLI::Option *opt, const std::string &modifier);
    /** modify a subcommand based on characters in a string*/
    static void modify_subcommand(CLI::App *app, const std::string &modifiers);
    /** return true if the app itself support conversiont to config files*/
    CLI11_NODISCARD bool supports_config_file() const { return !non_config_required; }
    int32_t val32{0};
    int16_t val16{0};
    int8_t val8{0};
    int64_t val64{0};

    uint32_t uval32{0};
    uint16_t uval16{0};
    uint8_t uval8{0};
    uint64_t uval64{0};

    std::atomic<int64_t> atomicval64{0};
    std::atomic<uint64_t> atomicuval64{0};

    double v1{0};
    float v2{0};

    std::vector<double> vv1{};
    std::vector<std::string> vstr{};

    std::vector<std::vector<double>> vecvecd{};
    std::vector<std::vector<std::string>> vvs{};
    std::optional<double> od1{};
    std::optional<std::string> ods{};
    std::optional<std::vector<std::string>> ovs{};
    std::pair<double, std::string> p1{};
    std::pair<std::vector<double>, std::string> p2{};
    std::tuple<int64_t, uint16_t, std::optional<double>> t1{};
    std::tuple<std::tuple<std::tuple<std::string, double, std::vector<int>>, std::string, double>,
               std::vector<int>,
               std::optional<std::string>>
        tcomplex{};
    std::tuple<std::tuple<std::tuple<std::string, double, std::vector<int>>, std::string, double>,
               std::vector<int>,
               std::optional<std::string>>
        tcomplex2{};
    std::vector<std::tuple<std::string, double, char, std::vector<std::string>>> vectup{};
    std::string_view vstrv = "";

    bool flag1{false};
    int flagCnt{0};
    std::atomic<bool> flagAtomic{false};

    intWrapper64 iwrap{0};
    doubleWrapper dwrap{0.0};
    stringWrapper swrap{};
    std::string buffer{};
    std::complex<double> cv3{0.0, 0.0};
    std::complex<float> cv4{0.0, 0.0};

    int intbuffer{0};
    std::atomic<double> doubleAtomic{0.0};

    // for testing restrictions and reduction methods
    std::vector<std::string> vstrA{};
    std::vector<std::string> vstrB{};
    std::vector<std::string> vstrC{};
    std::vector<std::string> vstrD{};
    std::vector<std::string> vstrE{};
    std::vector<std::string> vstrF{};
    std::string mergeBuffer{};
    std::vector<std::string> validator_strings{};
    std::vector<std::shared_ptr<std::pair<std::string, bool>>> custom_string_options{};
    std::vector<std::shared_ptr<std::pair<std::vector<std::string>, bool>>> custom_vector_options{};

  private:
    bool non_config_required{false};
};
}  // namespace CLI
