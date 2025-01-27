#include <iostream>
#include <string>
#include <chrono>

int main() {
    // 長さ100000の文字列を'a'で初期化
    std::string a(100000, 'a');

    // コピー操作の時間測定
    auto start_copy = std::chrono::high_resolution_clock::now();
    std::string b = a; // コピー操作
    auto end_copy = std::chrono::high_resolution_clock::now();
    auto copy_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_copy - start_copy).count();

    // ムーブ操作の時間測定
    auto start_move = std::chrono::high_resolution_clock::now();
    std::string c = std::move(a); // ムーブ操作
    auto end_move = std::chrono::high_resolution_clock::now();
    auto move_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_move - start_move).count();

    // 結果を表示
    std::cout << "コピー操作にかかった時間: " << copy_duration << " μs" << std::endl;
    std::cout << "移動操作にかかった時間: " << move_duration << " μs" << std::endl;

    return 0;
}