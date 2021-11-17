#pragma once

#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <vector>

#include "random.hpp"

using namespace std;

/* �}�X���Ƃ̐ݒ� */
class MINE {
public:
	/* �Ώۂ̃}�X���J����ꂽ���̔��� */
	bool open;
	/* �Ώۂ̃}�X�̒n���̗L�� */
	bool mine;
	/* �`�F�b�N�̗L�� */
	bool check;

	/* �R���X�g���N�^ */
	MINE() : open(false), mine(false), check(false) {}
};

class FIELD {
private:
	int field_size;
	vector<vector<MINE>> field;

public:
	/* �R���X�g���N�^ */
	FIELD(int _field_size) : field_size(_field_size) {
		/* �}�X�̏����� */
		field.resize(field_size);
		for (int i = 0; i < field_size; i++) {
			field[i].resize(field_size);
		}
		/* �n���̐ݒu */
		int mine_number = 0, tmp_x, tmp_y;
		while (mine_number < field_size * field_size / 10) {
			tmp_x = (rnd() - 1e-6) * field_size, tmp_y = (rnd() - 1e-6) * field_size;
			if (field[tmp_x][tmp_y].mine == false){
				mine_number++;
				field[tmp_x][tmp_y].mine = true;
			}
		}
	}

	/* �f�X�g���N�^ */
	~FIELD() {
		delete &field_size;
		delete &field;
	}

	/* �Z�b�^�\ */
	void set_open(int _x, int _y, bool open_status) {
		field[_x][_y].open = open_status;
	}
	void set_mine(int _x, int _y, bool mine_status) {
		field[_x][_y].open = mine_status;
	}
	void set_check(int _x, int _y, bool check_status) {
		field[_x][_y].check = check_status;
	}
	/* �Q�b�^�[ */
	int get_field_size() const {
		return field_size;
	}
	bool is_open(int _x, int _y) const {
		return field[_x][_y].open;
	}
	bool is_mine(int _x, int _y) const {
		return field[_x][_y].mine;
	}
	bool is_check(int _x, int _y) const {
		return field[_x][_y].check;
	}

	/* �\�� */
	template <class T> void display(T cursor) {
		system("cls");
		for (int y = 0; y < field_size; y++) {
			for (int x = 0; x < field_size; x++) {
				/* �J�[�\���\�� */
				if (x == cursor.x && y == cursor.y) cout << "��";
				/* �J�����}�X�̕\�� */
				else if (field[x][y].open) {
					/* �n���}�X */
					if (field[x][y].mine) cout << "��";
					/* �󔒃}�X */
					else cout << " " << around_mine_count(x, y);
				}
				/* �`�F�b�N�}�X�̕\�� */
				else if (field[x][y].check) {
					cout << "�~";
				}
				/* �J���ĂȂ��}�X�̕\�� */
				else cout << "��";
			}
			cout << endl;
		}
	}

	/* �n�������ׂČ��������̔��� */
	void check_all_mine() const {
		for (int y = 0; y <= field_size - 1; y++) {
			for (int x = 0; x <= field_size - 1; x++) {
				if ((field[x][y].mine == true and field[x][y].check != true) or (field[x][y].mine != true and field[x][y].check == true)){
					return;
				}
			}
		}
		cout << "Game Clear!!" << endl;
		delete this;
		exit(0);
	}

	/* ����̒n���̐��̃J�E���g */
	int around_mine_count(int _x, int _y) {
		int count = 0;
		for (int y = max(0, _y - 1); y <= min(_y + 1, field_size - 1); y++) {
			for (int x = max(0, _x - 1); x <= min(_x + 1, field_size - 1); x++) {
				if (field[x][y].mine == true) count++;
			}
		}
		return count;
	}
	void around_search(int _x, int _y) {
		for (int y = max(0, _y - 1); y <= min(_y + 1, field_size-1); y++) {
			for (int x = max(0, _x - 1); x <= min(_x + 1, field_size-1); x++) {
				/* ����̒n������0�̃}�X�̏ꍇ�C�}�X��W�J */
				if (around_mine_count(x, y) == 0 && field[x][y].open == false) {
					/*  */
					for (int y1 = max(0, y - 1); y1 <= min(y + 1, field_size - 1); y1++) {
						for (int x1 = max(0, x - 1); x1 <= min(x + 1, field_size - 1); x1++) {
							/*  */
							if (field[x1][y1].open == false) {
								set_open(x1, y1, true);
								around_search(x1, y1);
							}
						}
					}
				}
			}
		}
	}
};

#endif
