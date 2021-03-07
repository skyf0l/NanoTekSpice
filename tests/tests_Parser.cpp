/*
** EPITECH PROJECT, 2021
** TESTS_PARSER
** File description:
** Test Parser
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <ComponentFactory.hpp>
#include <Parser.hpp>
#include <NtsException.hpp>

#define TEST_OK(name, path)                                        \
    Test(ParserOK, name, .init = cr_redirect_stdout)               \
    {                                                              \
        nts::loadFactoryComponents("./components");                \
        std::unique_ptr<nts::Circuit> circuit(new nts::Circuit()); \
        nts::Parser::LoadComponentsFromFile(path, circuit);        \
        circuit->simulate();                                       \
        circuit->display();                                        \
        circuit->simulate();                                       \
        circuit->display();                                        \
    }

#define TEST_KO(name, path)                                            \
    Test(ParserOK, name)                                               \
    {                                                                  \
        nts::loadFactoryComponents("./components");                    \
        try                                                            \
        {                                                              \
            std::unique_ptr<nts::Circuit> circuit(new nts::Circuit()); \
            nts::Parser::LoadComponentsFromFile(path, circuit);        \
            cr_assert(0);                                              \
        }                                                              \
        catch (nts::NtsException & e)                                  \
        {                                                              \
            cr_assert(1);                                              \
        }                                                              \
    }

// subject_sample
TEST_OK(subject_sample_clock, "tests/circuits/valids/subject_sample/clock.nts")
TEST_OK(subject_sample_or_gate, "tests/circuits/valids/subject_sample/or_gate.nts")
TEST_KO(subject_sample_bad, "tests/circuits/valids/subject_sample/bad.nts")

// valids
TEST_OK(4030_xor, "tests/circuits/valids/nts_single/4030_xor.nts")
TEST_OK(logger, "tests/circuits/valids/nts_single/logger.nts")
TEST_OK(input_output, "tests/circuits/valids/nts_single/input_output.nts")
TEST_OK(true, "tests/circuits/valids/nts_single/true.nts")
TEST_OK(4081_and, "tests/circuits/valids/nts_single/4081_and.nts")
TEST_OK(4801_ram, "tests/circuits/valids/nts_single/4801_ram.nts")
TEST_OK(4013_flipflop, "tests/circuits/valids/nts_single/4013_flipflop.nts")
TEST_OK(4069_not, "tests/circuits/valids/nts_single/4069_not.nts")
TEST_OK(false, "tests/circuits/valids/nts_single/false.nts")
TEST_OK(4017_johnson, "tests/circuits/valids/nts_single/4017_johnson.nts")
TEST_OK(4008_adder, "tests/circuits/valids/nts_single/4008_adder.nts")
TEST_OK(2716_rom, "tests/circuits/valids/nts_single/2716_rom.nts")
TEST_OK(clock, "tests/circuits/valids/nts_single/clock.nts")
TEST_OK(4001_nor, "tests/circuits/valids/nts_single/4001_nor.nts")
TEST_OK(4514_decoder, "tests/circuits/valids/nts_single/4514_decoder.nts")
TEST_OK(4071_or, "tests/circuits/valids/nts_single/4071_or.nts")
TEST_OK(4011_nand, "tests/circuits/valids/nts_single/4011_nand.nts")
TEST_OK(4512_selector, "tests/circuits/valids/nts_single/4512_selector.nts")
TEST_OK(4094_shift, "tests/circuits/valids/nts_single/4094_shift.nts")
TEST_OK(4040_counter, "tests/circuits/valids/nts_single/4040_counter.nts")
TEST_OK(and_or_not, "tests/circuits/valids/nts_advanced/and-or-not.nts")
TEST_OK(and, "tests/circuits/valids/nts_advanced/and.nts")
TEST_OK(altered_counter, "tests/circuits/valids/nts_advanced/altered-counter.nts")

TEST_OK(counter_comment, "tests/circuits/valids/counter_comment.nts")
TEST_OK(two_links_from_output, "tests/circuits/valids/two_links_from_output.nts")
TEST_OK(value_input, "tests/circuits/valids/value_input.nts")
TEST_OK(value_clock, "tests/circuits/valids/value_clock.nts")
TEST_OK(value_rom, "tests/circuits/valids/value_rom.nts")

// invalids
TEST_KO(invalid_path, "")
TEST_KO(null_targer, "/dev/null")
TEST_KO(urandom, "/dev/urandom")
TEST_KO(directory_target, "tests/")
TEST_KO(not_exist_targer, "tests/circuits/invalids/not_exist")

TEST_KO(text_before_chipsets_section, "tests/circuits/invalids/text_before_chipsets_section.nts")
TEST_KO(invalid_chipsets_section_content_2, "tests/circuits/invalids/invalid_chipsets_section_content_2.nts")
TEST_KO(invalid_links_section_content_1, "tests/circuits/invalids/invalid_links_section_content_1.nts")
TEST_KO(invalid_links_section_content_5, "tests/circuits/invalids/invalid_links_section_content_5.nts")
TEST_KO(invalid_links_section_content_4, "tests/circuits/invalids/invalid_links_section_content_4.nts")
TEST_KO(invalid_chipsets_section_content_1, "tests/circuits/invalids/invalid_chipsets_section_content_1.nts")
TEST_KO(invalid_links_section_content_2, "tests/circuits/invalids/invalid_links_section_content_2.nts")
TEST_KO(miss_chipsets_section, "tests/circuits/invalids/miss_chipsets_section.nts")
TEST_KO(invalid_section, "tests/circuits/invalids/invalid_section.nts")
TEST_KO(invalid_links_section_content_3, "tests/circuits/invalids/invalid_links_section_content_3.nts")
TEST_KO(miss_links_section, "tests/circuits/invalids/miss_links_section.nts")
TEST_KO(two_same_names, "tests/circuits/invalids/two_same_names.nts")
TEST_KO(unknown_name, "tests/circuits/invalids/unknown_name.nts")

TEST_KO(negative_pin, "tests/circuits/invalids/negative_pin.nts")
TEST_KO(invalid_pin_1, "tests/circuits/invalids/invalid_pin_1.nts")
TEST_KO(invalid_pin_2, "tests/circuits/invalids/invalid_pin_2.nts")
TEST_KO(invalid_pin_3, "tests/circuits/invalids/invalid_pin_3.nts")
TEST_KO(invalid_pin_4, "tests/circuits/invalids/invalid_pin_4.nts")

TEST_KO(two_links_in_input, "tests/circuits/invalids/two_links_in_input.nts")
TEST_KO(link_input_to_input, "tests/circuits/invalids/link_input_to_input.nts")
TEST_KO(link_input_to_itself, "tests/circuits/invalids/link_input_to_itself.nts")
TEST_KO(link_output_to_itself, "tests/circuits/invalids/link_output_to_itself.nts")

TEST_KO(invalid_value_1, "tests/circuits/invalids/invalid_value_1.nts")
TEST_KO(invalid_value_2, "tests/circuits/invalids/invalid_value_2.nts")
TEST_KO(invalid_value_format_1, "tests/circuits/invalids/invalid_value_format_1.nts")
TEST_KO(invalid_value_format_2, "tests/circuits/invalids/invalid_value_format_2.nts")
TEST_KO(invalid_value_format_3, "tests/circuits/invalids/invalid_value_format_3.nts")

TEST_KO(invalid_rom_1, "tests/circuits/invalids/invalid_rom_1.nts")
TEST_KO(invalid_rom_2, "tests/circuits/invalids/invalid_rom_2.nts")