#include "gtest/gtest.h"
#include <iostream>

#define SYMBOL_CONTAINER_PUBLIC public:
#include "symbol_container.h"


TEST( has_item, does_have ) {
    Symbol_Container container( "D:/TemporaryFiles/Post-Machine-Emulator/unit_tests/input_files/test_file_1" );
    EXPECT_TRUE( container.has_item('d') );
}

TEST( has_item, doesnt_have ) {
    Symbol_Container container( "D:/TemporaryFiles/Post-Machine-Emulator/unit_tests/input_files/test_file_1" );
    EXPECT_FALSE( container.has_item('k') );
}

TEST( m_symbols, simple_output ) {
    Symbol_Container container( "D:/TemporaryFiles/Post-Machine-Emulator/unit_tests/input_files/test_file_1" );
    std::cout << container.m_symbols << std::endl;
}

TEST( push_symbols, does_have ) {
    Symbol_Container container("D:/TemporaryFiles/Post-Machine-Emulator/unit_tests/input_files/test_file_1");
    container.push_symbols("123");
    EXPECT_TRUE(container.has_item('d') && container.has_item('1'));
}

TEST( get_symbols, _ ) {
    Symbol_Container container;
    container.push_symbols("abcdefg");
    EXPECT_EQ(0, container.get_symbols().compare("abcdefg"));
}
