#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// ─── Class 1: Reads raw lines from a file ────────────────────────────────────
class DataReader {
public:
    explicit DataReader(const std::string& filename) : filename_(filename) {}

    std::vector<std::string> read() const {
        std::vector<std::string> lines;
        std::ifstream file(filename_);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename_ << "\n";
            return lines;
        }
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }

private:
    std::string filename_;
};

// ─── Class 2: Formats raw lines into a readable report string ─────────────────
class ReportFormatter {
public:
    std::string format(const std::vector<std::string>& lines) const {
        std::string report = "===== REPORT =====\n";
        for (size_t i = 0; i < lines.size(); ++i) {
            report += std::to_string(i + 1) + ". " + lines[i] + "\n";
        }
        report += "==================\n";
        return report;
    }
};

// ─── Class 3: Prints a formatted string to console ───────────────────────────
class ConsolePrinter {
public:
    void print(const std::string& content) const {
        std::cout << content;
    }
};

// ─── Class 4: Sends a formatted string via email ─────────────────────────────
class EmailNotifier {
public:
    explicit EmailNotifier(const std::string& recipient) : recipient_(recipient) {}

    void send(const std::string& content) const {
        std::cout << "[EMAIL] Sending to " << recipient_ << "\n";
        std::cout << "[EMAIL] Body:\n" << content;
    }

private:
    std::string recipient_;
};

// ─── Facade: Hides the pipeline — caller just calls generate() ───────────────
class ReportFacade {
public:
    ReportFacade(const std::string& filename, const std::string& recipient)
        : reader_(filename), notifier_(recipient) {}

    void generate() {
        auto lines          = reader_.read();
        std::string report  = formatter_.format(lines);
        printer_.print(report);
        notifier_.send(report);
    }

private:
    DataReader      reader_;
    ReportFormatter formatter_;
    ConsolePrinter  printer_;
    EmailNotifier   notifier_;
};

int main() {
    ReportFacade facade("data.txt", "manager@company.com");
    facade.generate();
    return 0;
}