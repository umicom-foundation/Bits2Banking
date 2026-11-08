/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/wt-profile/profile_application.cpp
 *
 * PURPOSE:
 *   Adapt one Wt session to the Framework profile-name service.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "profile_application.h"
/* The narrow header keeps this view independent of account persistence.
 * The earlier account-wide include remains for interface review. */
#if 0
#include "umicom/security/local_profile.h"
#endif
#include "umicom/security/profile_name.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <string>

/* Each application owns its widget tree. No global input or result widget is
 * shared between browser sessions. C++ supplies Wt ownership and event binding;
 * Framework C owns the validation rule used by desktop and web consumers. */
std::unique_ptr<Wt::WApplication> CreateProfileApplication(const Wt::WEnvironment &environment)
{
    std::unique_ptr<Wt::WApplication> application = std::make_unique<Wt::WApplication>(environment);
    application->setTitle("Umicom - Profile name laboratory");
    application->root()->addNew<Wt::WText>("Choose a profile name: 3 to 48 ASCII letters, digits, - or _, starting with a letter.");
    Wt::WLineEdit *input = application->root()->addNew<Wt::WLineEdit>();
    input->setObjectName("profile-input");
    input->setAttributeValue("aria-label", "Profile name");
    Wt::WPushButton *check = application->root()->addNew<Wt::WPushButton>("Check name");
    check->setObjectName("profile-check");
    Wt::WText *result = application->root()->addNew<Wt::WText>("Enter a name, then choose Check name.");
    result->setObjectName("profile-result");
    result->setTextFormat(Wt::TextFormat::Plain);
    const auto validate = [input, result]() {
        const std::string bytes = input->text().toUTF8();
        char canonical[UMI_LOCAL_PROFILE_NAME_CAPACITY];
        const UmiStatus status = UmiLocalProfileNameBytes(bytes.data(), bytes.size(), canonical);
        if (status == UMI_STATUS_OK) {
            result->setText(Wt::WString::fromUTF8(std::string("Accepted name: ") + canonical));
        } else {
            result->setText("Name rejected. Use 3 to 48 ASCII letters, digits, - or _, starting with a letter.");
        }
    };
    check->clicked().connect(validate);
    input->enterPressed().connect(validate);
    return application;
}
