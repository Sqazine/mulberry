#pragma once
// #include <string>
// #include <cstdint>
// #include <unordered_map>
// #include <cstdint>
// #include "fmod_studio.hpp"
// class AudioEvent
// {
// public:
// 	AudioEvent();

// 	bool IsValid();
// 	void Restart();
// 	void Stop(bool isFadeOut=true);

// 	void SetPaused(bool isPaused);
// 	bool GetPaused() const;

// 	void SetVolume(float value);
// 	float GetVolume() const;

// 	void SetPitch(float value);
// 	float GetPitch() const;

// 	void Setparameter(const std::string& name,float value);
// 	float GetParameter(const std::string& name);

// 	bool Is3DAudio() const;
// 	void Set3DAttributes(const class Matrix4& worldMatrix);
// protected:
// 	friend class Audio;

// 	AudioEvent(class Audio* audioSystem, uint32_t id);
// private:
// 	class Audio* m_System;
// 	uint32_t m_ID;
// };

// //由于FMOD使用左手坐标系，而Opengl和Vulkan使用右手坐标系，因此需要转换
// struct FMOD_VECTOR ToFMODVector3(const class Vector3& vec3);

// class AudioSystem
// {
// public:
// 	AudioSystem(class Application* app);
// 	~AudioSystem();

// 	void Update(float deltaTime);

// 	void Loadbank(const std::string& name);
// 	void UnLoadBank(const std::string& name);
// 	void UnloadAllBank();

// 	void SetBusVolume(const std::string& name,float value);
// 	float GetBusVolume(const std::string& name) const;
// 	void SetBusPaused(const std::string& name,bool isPaused);
// 	bool GetBusPaused(const std::string& name) const;

// 	class AudioEvent* PlayEvent(const std::string& name);

// 	void SetListener(const class Matrix4& viewMatrix);
// protected:
// 	friend class AudioEvent;
// 	FMOD::Studio::EventInstance* GetEventInstance(uint32_t eventID);
// private:
// 	class Application* m_Application;

// 	FMOD::Studio::System* m_System;

// 	FMOD::System* m_CoreSystem;
// 	//已加载的存储库
// 	std::unordered_map<std::string, FMOD::Studio::Bank*> m_Banks;
// 	//已加载的时间
// 	std::unordered_map<std::string, FMOD::Studio::EventDescription*> m_EventDescriptions;

// 	std::unordered_map<uint32_t, FMOD::Studio::EventInstance*> m_EventInstances;

// 	std::unordered_map<std::string, FMOD::Studio::Bus*> m_Buses;

// 	static uint32_t m_NextID;
// };