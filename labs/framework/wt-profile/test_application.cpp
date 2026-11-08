/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/wt-profile/test_application.cpp
 *
 * PURPOSE:
 *   Exercise the production Wt widget signals and shared C boundary without starting an HTTP listener.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "profile_application.h"
#include <Wt/Test/WTestEnvironment.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WEvent.h>
#include <cstdio>
#include <cstring>
#include <string>
#define CHECK(value) do { if (!(value)) { std::fprintf(stderr, "line %d: %s\n", __LINE__, #value); return 1; } } while (0)

static int Exercise(const char *mode)
{
    /* Construct the environment before the application and destroy the view
     * first. Widget pointers are borrowed only within this session's lifetime. */
    Wt::Test::WTestEnvironment environment;
    auto application = CreateProfileApplication(environment);
    CHECK(application != nullptr);
    auto *input = dynamic_cast<Wt::WLineEdit *>(application->root()->find("profile-input"));
    auto *button = dynamic_cast<Wt::WPushButton *>(application->root()->find("profile-check"));
    auto *result = dynamic_cast<Wt::WText *>(application->root()->find("profile-result"));
    CHECK(input != nullptr && button != nullptr && result != nullptr);
    CHECK(input->text().toUTF8().empty());
    CHECK(result->text().toUTF8() == "Enter a name, then choose Check name.");
    CHECK(result->textFormat() == Wt::TextFormat::Plain);
    const auto submit = [input, button](const std::string &text) {
        input->setText(Wt::WString::fromUTF8(text));
        button->clicked().emit(Wt::WMouseEvent());
    };
    const auto rejected = [result]() {
        return result->text().toUTF8() ==
            "Name rejected. Use 3 to 48 ASCII letters, digits, - or _, starting with a letter.";
    };
    if (!std::strcmp(mode, "initial")) return 0;
    if (!std::strcmp(mode, "click") || !std::strcmp(mode, "fresh-session")) {
        submit("Alice_7");
        CHECK(result->text().toUTF8() == "Accepted name: alice_7");
    } else if (!std::strcmp(mode, "enter")) {
        input->setText("Bob-8"); input->enterPressed().emit();
        CHECK(result->text().toUTF8() == "Accepted name: bob-8");
        input->setText("../../other"); input->enterPressed().emit();
        CHECK(rejected());
    } else if (!std::strcmp(mode, "boundaries")) {
        submit("Ab"); CHECK(rejected());
        submit("Abc"); CHECK(result->text().toUTF8() == "Accepted name: abc");
        submit(std::string(48U, 'A'));
        CHECK(result->text().toUTF8() == std::string("Accepted name: ") + std::string(48U, 'a'));
        submit(std::string(49U, 'A')); CHECK(rejected());
        submit(""); CHECK(rejected());
    } else if (!std::strcmp(mode, "embedded-nul")) {
        submit(std::string("Alice\0Bob", 9U)); CHECK(rejected());
    } else if (!std::strcmp(mode, "unicode")) {
        submit(std::string("Al\xc3\xaf" "ce")); CHECK(rejected());
    } else if (!std::strcmp(mode, "plain-output")) {
        submit("<script>alert(1)</script>"); CHECK(rejected());
        CHECK(result->textFormat() == Wt::TextFormat::Plain);
        CHECK(result->text().toUTF8().find("<script>") == std::string::npos);
    } else if (!std::strcmp(mode, "repeated")) {
        for (unsigned i = 0U; i < 32U; ++i) {
            submit("Good_Name"); CHECK(result->text().toUTF8() == "Accepted name: good_name");
            submit("2bad"); CHECK(rejected());
        }
    } else return 2;
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    int status = Exercise(argv[1]);
    /* A new application must begin empty after the previous session is gone.
     * This checks re-creation, not concurrent browser-session isolation. */
    if (status == 0 && !std::strcmp(argv[1], "fresh-session")) status = Exercise("initial");
    return status;
}
