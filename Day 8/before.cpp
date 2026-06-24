#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// BAD: This single class does 4 completely different jobs.
// Any change to file format, print style, or email server
// forces you to edit THIS class. One class, four reasons to change.

class Report {
public:
    std::string filename;

    // Job 1: Reading data from a file
    std::vector<std::string> readData() {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << "\n";
            return lines;
        }
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }

    // Job 2: Formatting the data
    std::string formatData(const std::vector<std::string>& lines) {
        std::string report = "===== REPORT =====\n";
        for (size_t i = 0; i < lines.size(); ++i) {
            report += std::to_string(i + 1) + ". " + lines[i] + "\n";
        }
        report += "==================\n";
        return report;
    }

    // Job 3: Printing to console
    void printToConsole(const std::string& formattedReport) {
        std::cout << formattedReport;
    }

    // Job 4: Sending an email — completely different responsibility
    void sendEmail(const std::string& formattedReport) {
        // Simulated email send (no real SMTP here)
        std::cout << "[EMAIL] Sending report to manager@company.com\n";
        std::cout << "[EMAIL] Body:\n" << formattedReport;
    }

    // One function that chains all four jobs together
    void generate() {
        auto lines = readData();
        std::string formatted = formatData(lines);
        printToConsole(formatted);
        sendEmail(formatted);
    }
};

int main() {
    Report r;
    r.filename = "data.txt";
    r.generate();
    return 0;
}