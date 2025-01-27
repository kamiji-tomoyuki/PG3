#include <iostream>
#include <string>
#include <chrono>

int main() {
    // ����100000�̕������'a'�ŏ�����
    std::string a(100000, 'a');

    // �R�s�[����̎��ԑ���
    auto start_copy = std::chrono::high_resolution_clock::now();
    std::string b = a; // �R�s�[����
    auto end_copy = std::chrono::high_resolution_clock::now();
    auto copy_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_copy - start_copy).count();

    // ���[�u����̎��ԑ���
    auto start_move = std::chrono::high_resolution_clock::now();
    std::string c = std::move(a); // ���[�u����
    auto end_move = std::chrono::high_resolution_clock::now();
    auto move_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_move - start_move).count();

    // ���ʂ�\��
    std::cout << "�R�s�[����ɂ�����������: " << copy_duration << " ��s" << std::endl;
    std::cout << "�ړ�����ɂ�����������: " << move_duration << " ��s" << std::endl;

    return 0;
}