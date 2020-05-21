/* 
 * File:   TestRun.h
 * Author: mccaffrey
 *
 * Created on February 26, 2020, 2:07 PM
 */

#ifndef TESTRUN_H
#define TESTRUN_H

#include <string>
#include <cstdlib>
#include <vector> 
#include "TestCase.h"
#include <jsoncpp/json/json.h>

using namespace std;

class TestRun {
private:
    string timestamp;
    string sha256;
    string filename;
    vector<TestCase> testCases;


public:

    string GetAsJson() {


        //TODO: Make the name of the name/value a const
        Json::Value testRuns;
        testRuns["DateTimeStamp"] = GetTimestamp();
        testRuns["Filename"] = GetFilename();
        testRuns["Sha256"] = GetSha256();
        Json::Value testCasesJson;

        for (int i = 0; i < testCases.size(); i++) {
            TestCase tc = testCases[i];
            testCasesJson[i]["TestCase"] = tc.GetTestCaseNumber();
            if (tc.GetH_original() != -1)
                testCasesJson[i]["HOriginal"] = tc.GetH_original();
            if (tc.GetH_bitstring() != -1)
                testCasesJson[i]["HBitstring"] = tc.GetH_bitstring();
            /*
            if (tc.GetMin() != "")
                testCasesJson[i]["Min"] = tc.GetMin();
            if (tc.GetH_min() != "")
                testCasesJson[i]["HMin"] = tc.GetH_min();
            if (tc.GetP_max() != "")
                testCasesJson[i]["PMax"] = tc.GetP_max();
             */
            if (tc.GetH_assessed() != -1)
                testCasesJson[i]["HAssessed"] = tc.GetH_assessed();
            if (tc.GetRet_min_entropy() != -1)
                testCasesJson[i]["RetMinEntropy"] = tc.GetRet_min_entropy();
            if (tc.GetData_word_size() != -1)
                testCasesJson[i]["DataWordSize"] = tc.GetData_word_size();
            if (tc.GetBin_t_tuple_res() != -1)
                testCasesJson[i]["BinTTupleRes"] = tc.GetBin_t_tuple_res();
            if (tc.GetT_tuple_res() != -1)
                testCasesJson[i]["TTupleRes"] = tc.GetT_tuple_res();
            if (tc.GetBin_lrs_res() != -1)
                testCasesJson[i]["BinLrsRes"] = tc.GetBin_lrs_res();
            if (tc.GetLrs_res() != -1)
                testCasesJson[i]["LrsRes"] = tc.GetLrs_res();
            if (tc.GetMean() != -1)
                testCasesJson[i]["Mean"] = tc.GetMean();
            if (tc.GetMedian() != -1)
                testCasesJson[i]["Median"] = tc.GetMedian();
            if (tc.GetBinary() == 0)
                testCasesJson[i]["Binary"] = false;
            else if (tc.GetBinary() == 1)
                testCasesJson[i]["Binary"] = true;
            if (tc.GetLiteral_mcv_estimate_mode() != -1)
                testCasesJson[i]["LiteralMCVEstimateMode"] = tc.GetLiteral_mcv_estimate_mode();
            if (tc.GetLiteral_mcv_estimate_p_hat() != -1)
                testCasesJson[i]["LiteralMCVEstimatePHat"] = tc.GetLiteral_mcv_estimate_p_hat();
            if (tc.GetLiteral_mcv_estimate_p_u() != -1)
                testCasesJson[i]["LiteralMCVEstimatePU"] = tc.GetLiteral_mcv_estimate_p_u();

            if (tc.GetBitstring_mcv_estimate_mode() != -1)
                testCasesJson[i]["BitstringMCVEstimateMode"] = tc.GetBitstring_mcv_estimate_mode();
            if (tc.GetBitstring_mcv_estimate_p_hat() != -1)
                testCasesJson[i]["BitstringMCVEstimatePHat"] = tc.GetBitstring_mcv_estimate_p_hat();
            if (tc.GetBitstring_mcv_estimate_p_u() != -1)
                testCasesJson[i]["BitStringMCVEstimatePU"] = tc.GetBitstring_mcv_estimate_p_u();

            if (tc.GetChi_square_independence_score != -1)
                testCasesJson[i]["ChiSquareIndependenceScore"] = tc.GetChi_square_independence_score();
            if (tc.GetChi_square_independence_degress_of_freedom != -1)
                testCasesJson[i]["ChiSquareIndependenceDegressOfFreedom"] = tc.GetChi_square_independence_degress_of_freedom();
            if (tc.GetChi_square_independence_p_value != -1)
                testCasesJson[i]["ChiSquareIndependencePValue"] = tc.GetChi_square_independence_p_value();

            if (tc.GetChi_square_goodness_of_fit_score != -1)
                testCasesJson[i]["ChiSquareGoodnessOfFitScore"] = tc.GetChi_square_goodness_of_fit_score();
            if (tc.GetChi_square_goodness_of_fit_degress_of_freedom != -1)
                testCasesJson[i]["ChiSquareGoodnessOfFitDegressOfFreedom"] = tc.GetChi_square_goodness_of_fit_degress_of_freedom();
            if (tc.GetChi_square_goodness_of_fit_p_value != -1)
                testCasesJson[i]["ChiSquareGoodnessOfFitPValue"] = tc.GetChi_square_goodness_of_fit_p_value();

            if (tc.GetPassed_chi_square_tests == 0)
                testCasesJson[i]["PassedChiSquareTests"] = false;
            else if (tc.GetPassed_chi_square_tests() == 1)
                testCasesJson[i]["PassedChiSquareTests"] = true;

            if (tc.GetLongest_repeated_substring_p_col() != -1)
                testCasesJson[i]["LongestRepeatedSubstringPCol"] = tc.GetLongest_repeated_substring_p_col();
            if (tc.GetLongest_repeated_substring_length_of_lrs() != -1)
                testCasesJson[i]["LongestRepeatedSubstringLengthOfLrs"] = tc.GetLongest_repeated_substring_length_of_lrs;
            if (tc.GetLongest_repeated_substring_pr_x_1() != -1)
                testCasesJson[i]["LongestRepeatedSubstringPRX1"] = tc.GetLongest_repeated_substring_pr_x_1();

            if (tc.GetPassed_length_longest_repeated_substring_test() == 0)
                testCasesJson[i]["PassedLengthLongestRepeatedSubstring"] = false;
            else if (tc.GetPassed_length_longest_repeated_substring_test() == 1)
                testCasesJson[i]["PassedLengthLongestRepeatedSubstring"] = true;

        }

        testRuns["TestCases"] = testCasesJson;

        Json::StyledWriter styled;
        return styled.write(testRuns);

    }

    void AddTestCase(TestCase tc) {
        testCases.push_back(tc);
    }

    /*
    void AddTestCase(string testCaseNumber, string h_original, string h_bitstring, string min, string h_min, string p_max, string h_assessed) {
        TestCase tc(testCaseNumber, h_original, h_bitstring, min, h_min, p_max, h_assessed);
        testCases.push_back(tc);
    }
     */
    void SetTestCases(vector<TestCase> testCases) {
        this->testCases = testCases;
    }

    vector<TestCase> GetTestCases() const {
        return testCases;
    }

    void SetTimestamp(string timestamp) {
        this->timestamp = timestamp;
    }

    string GetTimestamp() const {
        return timestamp;
    }

    void SetSha256(string sha256) {
        this->sha256 = sha256;
    }

    string GetSha256() const {
        return sha256;
    }

    void SetFilename(string filename) {
        this->filename = filename;
    }

    string GetFilename() const {
        return filename;
    }

};

#endif /* TESTRUN_H */

