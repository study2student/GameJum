#pragma once
#include <chrono>

class SceneBase;
class Fader;
class Camera;

class SceneManager
{

public:

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		GAME,
		GAMEOVER
	};

	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static SceneManager& GetInstance(void);

	void Init(void);
	void Init3D(void);
	void Update(void);
	void Draw(void);
	bool Release(void);		// �������

	// ���\�[�X�̔j��
	void Destroy(void);

	// ��ԑJ��
	void ChangeScene(SCENE_ID nextId);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID(void);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void) const;

	// �J�����̎擾
	Camera* GetCamera(void) const;

	void SetAliveTimeP1(float aliveTimeP1);
	void SetAliveTimeP2(float aliveTimeP2);

	float GetAliveTimeP1(void);
	float GetAliveTimeP2(void);

private:

	// �ÓI�C���X�^���X
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;

	// �e��V�[��
	SceneBase* scene_;

	// �t�F�[�h
	Fader* fader_;

	// �J����
	Camera* camera_;

	// �V�[���J�ڒ�����
	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	// ��������
	float aliveTimeP1_;
	float aliveTimeP2_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager(void);
	// �R�s�[�R���X�g���N�^�����l
	SceneManager(const SceneManager& manager) = default;
	// �f�X�g���N�^�����l
	~SceneManager(void) = default;

	// �f���^�^�C�������Z�b�g����
	void ResetDeltaTime(void);

	// �V�[���J��
	void DoChangeScene(SCENE_ID sceneId);

	// �t�F�[�h
	void Fade(void);

	// �C���X�^���X�̔j��
	void Destory(void);

	// �w�肵���V�[���̉���֐�
	void ReleaseScene(SCENE_ID SceneID);		// �V�[���̉������

};

