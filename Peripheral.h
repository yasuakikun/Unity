#pragma once
class Peripheral
{
public:
	Peripheral();
	~Peripheral();

	//const bool 
		//
	//const bool IsTrigger() const;
	//����̃{�^����������Ă���B
	//���͂������{�^��
	bool IsPressing(int button)const;


	bool IsTrigger(int button)const;
	//���͍X�V�A���t���[���X�V����
	void Update();
private:
	int padState;//���݂̓��͏��
	int lastpadState;//���O�̃t���[�����͏��

};

