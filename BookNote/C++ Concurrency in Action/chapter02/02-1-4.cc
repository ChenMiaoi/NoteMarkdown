#include <iostream>
#include <string>
#include <thread>

enum class command {
    open_new_document,
};

struct user_command {
    command type;
};

void open_document_and_display_gui(const std::string&) {}
bool done_editing() { return {}; }
const std::string& get_filename_from_user() { return {}; }
void process_user_input(const user_command&) {}
user_command get_user_input() { return {}; }

void edit_document(const std::string& filename) {
    open_document_and_display_gui(filename);
    while (!done_editing()) {
        user_command cmd = get_user_input();
        if (cmd.type == command::open_new_document) {
            const std::string new_name = get_filename_from_user();
            std::thread t(edit_document, new_name);
            t.detach();
        } else {
            process_user_input(cmd);
        }
    }
}

int main() {

    return 0;
}