#include <vector>
#include <matplot/matplot.h>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <set>
#include <unordered_set>

void func_1_read(int& n, std::vector<int>& input, std::ifstream& fin) {
    fin >> n;
    for (int i = 0; i < n; i += 1) {
        fin >> input[i];
    }
}

void func_1_calc(int& n, std::vector<int>& input) {
    std::vector<int> as(200001, -1);

    for (int i = 0; i < n; i += 1) {
        int idx = input[i];
        as[idx] = n - i - 1;
    }
    std::cout << std::distance(as.begin(), std::max_element(as.begin(), as.end())) << "\n";
}

void func_2_read(int& n, std::vector<int>& data, std::ifstream& fin) {
    fin >> n;
    for (int i = 0; i < n; i += 1) {
        fin >> data[i];
    }
}

void func_2_calc(int& n, std::vector<int>& data) {
    std::unordered_set<int> unique;
    unique.reserve(200000);
    int idx_unique = n;
    for (int i = n - 1; 0 <= i; i -= 1) {
        if (unique.find(data[i]) != unique.end()) {
            idx_unique = data[i];
            unique.insert(idx_unique);
        }
    }
    std::cout << idx_unique << " ";
}

double timer_read(int& n, std::vector<int>& input, std::ifstream& fin, void (*func)(int& a, std::vector<int>& b, std::ifstream& c)) {
    auto reading_begin = std::chrono::steady_clock::now();
    func(n, input, fin);
    auto reading_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> read_time = reading_end - reading_begin;
    return read_time.count();
}

double timer_calc(int& n, std::vector<int>& input, void (*func)(int& a, std::vector<int>& b)) {
    auto calculations_begin = std::chrono::steady_clock::now();
    func(n, input);
    auto calculations_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> calculations_time = calculations_end - calculations_begin;
    return calculations_time.count();
}


void generate_data(std::string f, int n) {
    std::ofstream fout;
    fout.open(f);
    fout << n << '\n';
    for (int i = 0; i < n; ++i) fout << rand() % n + 1 << " ";
    fout.close();
}

int main() {

    std::vector<double> tn_calc1;
    std::vector<double> t_calc1;
    std::vector<double> tn_calc2;
    std::vector<double> t_calc2;
    std::vector<double> t_read1;
    std::vector<double> t_read2;

    for (int n = 2000; n <= 200000; n += 1000) {

        generate_data("data1.txt", n);
        std::ifstream fin1;
        fin1.open("data1.txt");
        if (!(fin1.is_open())) {
            std::cout << "FILE IS NOT OPEN\n";
            exit(-1);
        }

        std::ios_base::sync_with_stdio(0);
        fin1.tie(nullptr);

        std::vector<int> input1(200001, -1);
        std::vector<int> input2(200001, -1);

        double read1 = timer_read(n, input1, fin1, func_1_read);
        double read2 = timer_read(n, input2, fin1, func_2_read);

        t_read1.push_back(read1);
        t_read2.push_back(read2);

        fin1.close();

        double calc1 = timer_calc(n, input1, func_1_calc);
        double calc2 = timer_calc(n, input2, func_2_calc);

        tn_calc1.push_back(calc1 * 100000 / n);
        t_calc1.push_back(calc1);

        tn_calc2.push_back(calc2 * 100000 / n);
        t_calc2.push_back(calc2);

    }

    std::vector<double> x = matplot::linspace(5000, 200000, 200);
    matplot::plot(x, tn_calc1, x, tn_calc2, "--");
    matplot::xlabel("n");
    matplot::ylabel("t_{calculations}/n");
    //matplot::save("img/tcn(n).svg");
    //matplot::save("img/tcn(n).gif");
    matplot::save("img/tcn(n).png");

    matplot::plot(x, t_calc1, x, t_calc2, "--");
    matplot::xlabel("n");
    matplot::ylabel("t_{calculations}");
    //matplot::save("img/tc(n).svg");
    //matplot::save("img/tc(n).gif");
    matplot::save("img/tc(n).png");

    matplot::plot(x, t_read1, x, t_read2, "--");
    matplot::xlabel("n");
    matplot::ylabel("t_{reading}");
    //matplot::save("img/tr(n).svg");
    //matplot::save("img/tr(n).gif");
    matplot::save("img/tr(n).png");

}