#include <iostream>
#include <format>
#include <cstring>
#include <string>
#include <vector>
#include <charconv>
#include <string_view>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

// [1] C String
void doExample1();
char* copyString(const char* str); 
char* appendStrings(const char* str1, const char* str2, const char* str3);

// [2] String Literal
void doExample2();

// [3] C++ std::string
void doExample3();

// [4] Number Conversion
void doExample4();

// [5] std::string_view class
void doExample5();
std::string_view extractExtension(std::string_view filename);

// [6] String Formatting
void doExample6();

// [7] Custom Type
void doExample7();

class KeyValue {
public:
    KeyValue(std::string key, int value) : m_key{ std::move(key) }, m_value{ value } {}

    const std::string& getKey() const { return m_key; }
    int getValue() const { return m_value; }

private:
    std::string m_key;
    int m_value;
};

template<>
struct std::formatter<KeyValue> {
    constexpr auto parse(std::format_parse_context& ctx) {
        auto it = ctx.begin();
        auto end = ctx.end();

        if (it == end || *it == '}') {
            m_outputType = OutputType::KeyAndValue;
            return it;
        }

        switch (*it) {
        case 'a':
            m_outputType = OutputType::KeyOnly;
            break;
        case 'b':
            m_outputType = OutputType::ValueOnly;
            break;
        case 'c':
            m_outputType = OutputType::KeyAndValue;
            break;
        default:
            throw std::format_error("Invalid KeyValue format specifier.");
        }

        ++it;
        if (it != end && *it != '}') {
            throw std::format_error("Invalid KeyValue format specifier.");
        }
        return it;
    }

    auto format(const KeyValue& kv, std::format_context& ctx) const {
        switch (m_outputType) {
        case OutputType::KeyOnly:
            return std::format_to(ctx.out(), "{}", kv.getKey());
        case OutputType::ValueOnly:
            return std::format_to(ctx.out(), "{}", kv.getValue());
        default:
            return std::format_to(ctx.out(), "{} - {}", kv.getKey(), kv.getValue());
        }
    }

private:
    enum class OutputType { KeyOnly, ValueOnly, KeyAndValue };
    OutputType m_outputType{ OutputType::KeyAndValue };
};

int main() {
    doExample1();
    doExample2();
    doExample3();
    doExample4();
    doExample5();
    doExample6();
    doExample7();
    return 0;
}

void doExample1() {
    std::cout << std::endl;
    std::cout << "* Example 1: C string" << std::endl;
    const char* str1 = "hello"; 
    char* str2 = copyString(str1);
    std::cout << std::format("str1: {}, str2: {}", str1, str2) << std::endl;
    const char* str3 = "world!";
    char* str4 = appendStrings(str1, str2, str3);
    std::cout << std::format("str3: {}, str4: {}", str3, str4) << std::endl;
    delete[] str2;
    delete[] str4;

    char text1[] { "abcdef" };
    size_t s1 { sizeof(text1) };
    size_t s2 { strlen(text1) };
    std::cout << std::format("sizeof: {}, strlen: {}", s1, s2) << std::endl;
    const char* text2 { "abcdef" };
    size_t s3 { sizeof(text2) };
    size_t s4 { strlen(text2) };
    std::cout << std::format("sizeof: {}, strlen: {}", s3, s4) << std::endl;
}

char* copyString(const char* str) {
    char* result { new char[strlen(str) + 1] };
    strcpy(result, str);
    return result;
}

char* appendStrings(const char* str1, const char* str2, const char* str3) {
    char* result { new char[strlen(str1) + strlen(str2) + strlen(str3) + 1] };
    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, str3);
    return result;
}

void doExample2() {
    std::cout << std::endl;
    std::cout << "* Example 2: String Lateral" << std::endl;
    std::cout << "Hello" << std::endl;
    const char* str1 { R"(Hello "World"!
    Hello Again!)" };
    const char* str2 { R"d-char-sequence(r-char-sequence)d-char-sequence" };
    const char* str3 { R"-(Embedded )" characters)-" };
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
    std::cout << str3 << std::endl;
}

void doExample3() {
    std::cout << std::endl;
    std::cout << "* Example 3: C++ std::string" << std::endl;

    std::string a { "12" };
    std::string b { "34" };
    std::string c = a + b;
    std::cout << std::format("a: {}, b: {}, c: {}", a, b, c) << std::endl;
    auto result { a.compare(b) };
    if (result < 0) std::cout << "a is less than b" << std::endl;
    if (result > 0) std::cout << "a is greater than b" << std::endl;
    if (result == 0) std::cout << "a is equal to b" << std::endl;

    const char* d { "12" };
    char e[] { "12" };
    std::cout << std::format("d: {}, e: {} ; ",  d, e) 
              << ((d == e) ? "d and e is eqaul." : "d and e is not equal.") << std::endl;
    std::cout << std::format("d: {}, e: {} ; ",  d, e) 
              << (!strcmp(d, e) ? "d and e is eqaul." : "d and e is not equal.") << std::endl;
    
    std::string myString { "hello" };
    myString += ", there";
    std::string myOtherString { myString };
    if (myString == myOtherString) myOtherString[0] = 'H';
    std::cout << std::format("myString: {}, myOtherString: {}", myString, myOtherString) << std::endl;

    std::string strHello { "Hello!!" };
    std::string strWorld { "The World!"};
    auto position { strHello.find("!!") };
    if (position != std::string::npos) strHello.replace(position, 2, strWorld.substr(3, 6));
    std::cout << strHello << std::endl;

    // auto string1 { "Hello World" }; // const char*
    // auto string2 { "Hello World"s }; // std::string 
    // std::vector names { "John"s, "Sam"s, "Joe"s }; // std::string
}

void doExample4() {
    std::cout << std::endl;
    std::cout << "* Example 4: Number Conversion" << std::endl;

    // std::string to_string(T val);
    long double d { 3.14L };
    std::string s { std::to_string(d) };
    // stoi stol stoul stoll stoull stof stod stold
    const std::string toParse { " 123USD" };
    size_t index { 0 };
    int value { std::stoi(toParse, &index) };
    std::cout << std::format("Parsed value: {}", value) << std::endl;
    std::cout << std::format("First non-parsed character : '{}'", toParse[index]) << std::endl;

    // to_chars_result to_chars(char* first, char* last, IntegerT value, int base = 10);
    // IntegerT: signed or unsigned integer, or char
    /*
     * struct to_chars_result {
     *  char* ptr;
     *  errc ec;
     * }
     */
    const size_t BufferSize { 50 };
    std::string out(BufferSize, ' ');
    // auto result { std::to_chars(out.data(), out.data() + out.size(), 12345) };
    auto [ptr, error] { std::to_chars(out.data(), out.data() + out.size(), 12345) };
    if (error == std::errc{}) std::cout << out << std::endl;

    // to_chars_result to_chars(char* first, char* last, FloatT value);
    /*
     * enum class chars_format {
     *  scientific,
     *  fixed,
     *  hex,
     *  general = fixed | scientific
     * };
     */
    double value0 { 0.314 };
    std::string out0(BufferSize, ' ');
    auto [ptr0, error0] { std::to_chars(out0.data(), out0.data() + out0.size(), value0) }; 
    if (error0 == std::errc{}) std::cout << out0 << std::endl;

    // from_chars_result from_chars(const char* first, const char* last, IntegerT& value, int base = 10);
    // from_chars_result from_chars(const char* first, const char* last, FloatT& value, chars_format format = chars_format::general);
    /*
     * struct from_chars_results {
     *  const char* ptr;
     *  errc ec;
     * }
     */
    double value1 { 0.314 };
    std::string out1(BufferSize, ' ');
    auto [ptr1, error1] { std::to_chars(out1.data(), out1.data() + out1.size(), value1) };
    if (error1 == std::errc{}) std::cout << out1 << std::endl;
    double value2;
    auto [ptr2, error2] { std::from_chars(out1.data(), out1.data() + out1.size(), value2) };
    if (error2 == std::errc{}) {
        if (value1 == value2) std::cout << "Perfect roundtrip." << std::endl;
        else std::cout << "No Perfect roundtrip?!?" << std::endl;
    }
}

void doExample5() {
    std::cout << std::endl;
    std::cout << "* Example 5: std::string_view" << std::endl;

    std::string filename { R"(C:\temp\my file.ext)" };
    std::cout << std::format("C++ string: {}", extractExtension(filename)) << std::endl;
    const char* cString { R"(C:\temp\my file.ext)" };
    std::cout << std::format("C string: {}", extractExtension(cString)) << std::endl;
    std::cout << std::format("Literal: {}", extractExtension(R"(C:\temp\my file.ext)")) << std::endl;

    // const char* raw { /* ... */ };
    // size_t length { /* ... */ };
    // std::cout << std::format("Raw: {}",  extractExtension({raw, length})) << std::endl;
    // std::cout << std::format("Raw: {}",  extractExtension(std::string_view {raw, length})) << std::endl;

    // void handleExtension(const std::string& extension);
    // handleExtension(extractExtension("my file.ext").data());
    // handleExtension(std::string { extractExtension("my file.ext") });

    std::string str { "Hello" };
    std::string_view sv { " world" };
    auto result1 { str + sv.data() };
    std::string result2 = { str };
    result2.append(sv.data(), sv.size());
    std::cout << std::format("result1: {}, result2: {}", result1, result2) << std::endl;

    auto sv0 { "My string_view"sv };
    std::cout << sv0 << std::endl;
    std::cout << sv0.data() << std::endl;
}

std::string_view extractExtension(std::string_view filename) {
    return filename.substr(filename.rfind("."));
}

void doExample6() {
    std::cout << std::endl;
    std::cout << "* Example 6: String Formatting" << std::endl;

    int n = 4;
    auto s1 { std::format("Read {} bytes from {}", n, "file1.txt") };
    auto s2 { std::format("Read {0} bytes from {1}", n, "file1.txt") };
    auto s3 { std::format("Read {1} bytes from {0}", n, "file1.txt") };
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;

    // [[fill]align][sign][#][0][width][.precision][type]
    int i { 42 };
    // Width
    std::cout << std::format("|{:5}|", i) << std::endl;
    std::cout << std::format("|{:{}}|", i, 7) << std::endl;

    // [fill]align
    std::cout << std::format("|{:7}|", i) << std::endl;
    std::cout << std::format("|{:<7}|", i) << std::endl;
    std::cout << std::format("|{:_>7}|", i) << std::endl;
    std::cout << std::format("|{:_^7}|", i) << std::endl;

    // sign
    std::cout << std::format("|{:<5}|", i) << std::endl;
    std::cout << std::format("|{:<+5}|", i) << std::endl;
    std::cout << std::format("|{:< 5}|", i) << std::endl;
    std::cout << std::format("|{:< 5}|", -i) << std::endl;

    // # type
    std::cout << std::format("|{:10d}|", i) << std::endl;
    std::cout << std::format("|{:10b}|", i) << std::endl;
    std::cout << std::format("|{:#10b}|", i) << std::endl;
    std::cout << std::format("|{:10X}|", i) << std::endl;
    std::cout << std::format("|{:#10X}|", i) << std::endl;
    std::string s { "ProCpp" };
    std::cout << std::format("|{:_^10}|", s) << std::endl;

    // precision
    double d { 3.1415 / 2.3 };
    std::cout << std::format("|{:12g}|", d) << std::endl;
    std::cout << std::format("|{:12.2}|", d) << std::endl;
    std::cout << std::format("|{:12e}|", d) << std::endl;
    int width { 12 };
    int precision { 3 };
    std::cout << std::format("|{2:{0}.{1}f}|", width, precision, d) << std::endl;

    // 0
    std::cout << std::format("|{:06d}|", i) << std::endl;
    std::cout << std::format("|{:+06d}|", i) << std::endl;
    std::cout << std::format("|{:06X}|", i) << std::endl;
    std::cout << std::format("|{:#06X}|", i) << std::endl;

    // std::format_error
    // try {
    //     std::cout << std::format("An integer: {:.}", 5) << std::endl;
    // } catch (const std::format_error& e) {
    //     std::cout << e.what() << std::endl;
    // }
}

void doExample7() {
    std::cout << std::endl;
    std::cout << "* Example 7: Custom Type" << std::endl;

    KeyValue keyValue { "Key1", 11 };
    std::cout << std::format("{}", keyValue) << std::endl;
    std::cout << std::format("{:a}", keyValue) << std::endl;
    std::cout << std::format("{:b}", keyValue) << std::endl;
    std::cout << std::format("{:c}", keyValue) << std::endl;
    // try { std::cout << std::format("{:cd}", keyValue) << std::endl; }
    // catch (const std::format_error& e) { std::cout << e.what() << std::endl; }
}