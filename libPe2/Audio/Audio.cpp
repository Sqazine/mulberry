// #include "Audio.h"

// AudioEvent::AudioEvent()
//     : m_System(nullptr), m_ID(0)
// {
// }

// AudioEvent::AudioEvent(AudioSystem *audioSystem, uint32_t id)
//     : m_System(audioSystem), m_ID(id)
// {
// }

// bool AudioEvent::IsValid()
// {
//     return (m_System && m_System->GetEventInstance(m_ID) != nullptr);
// }
// void AudioEvent::Restart()
// {
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//         event->start();
// }
// void AudioEvent::Stop(bool isFadeOut)
// {
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//     {
//         FMOD_STUDIO_STOP_MODE mode = isFadeOut ? FMOD_STUDIO_STOP_ALLOWFADEOUT : FMOD_STUDIO_STOP_IMMEDIATE;
//         event->stop(mode);
//     }
// }
// void AudioEvent::SetPaused(bool isPaused)
// {
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//         event->setPaused(isPaused);
// }

// bool AudioEvent::GetPaused() const
// {
//     bool isPaused = false;
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//         event->getPaused(&isPaused);
//     return isPaused;
// }

// void AudioEvent::SetVolume(float value)
// {
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//         event->setVolume(value);
// }

// float AudioEvent::GetVolume() const
// {
//     float volume = 0.0f;
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//         event->getVolume(&volume);
//     return volume;
// }

// void AudioEvent::SetPitch(float value)
// {
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//         event->setPitch(value);
// }

// float AudioEvent::GetPitch() const
// {
//     float pitch = 0.0f;
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//         event->getPitch(&pitch);
//     return pitch;
// }

// void AudioEvent::Setparameter(const std::string &name, float value)
// {
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//         event->setParameterByName(name.c_str(), value);
// }

// float AudioEvent::GetParameter(const std::string &name)
// {
//     float parameter = 0.0f;
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//         event->getParameterByName(name.c_str(), &parameter);
//     return parameter;
// }

// bool AudioEvent::Is3DAudio() const
// {
//     bool is3D = false;
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//     {
//         FMOD::Studio::EventDescription *eventDescrition = nullptr;
//         event->getDescription(&eventDescrition);
//         if (eventDescrition)
//             eventDescrition->is3D(&is3D);
//     }
//     return is3D;
// }

// void AudioEvent::Set3DAttributes(const Matrix4 &worldMatrix)
// {
//     auto *event = m_System ? m_System->GetEventInstance(m_ID) : nullptr;
//     if (event)
//     {
//         FMOD_3D_ATTRIBUTES attr;
//         attr.position = ToFMODVector3(Vector3(worldMatrix.mat[12], worldMatrix.mat[13], worldMatrix.mat[14]));
//         attr.forward = ToFMODVector3(Vector3(worldMatrix.mat[2], worldMatrix.mat[6], worldMatrix.mat[10]));
//         attr.up = ToFMODVector3(Vector3(worldMatrix.mat[1], worldMatrix.mat[5], worldMatrix.mat[9]));
//         attr.velocity = {0.0f, 0.0f, 0.0f};
//         event->set3DAttributes(&attr);
//     }
// }

// uint32_t AudioSystem::m_NextID = 0;

// AudioSystem::AudioSystem(Application *app)
//     : m_Application(app), m_System(nullptr), m_CoreSystem(nullptr)
// {
//     FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR, FMOD_DEBUG_MODE_TTY);

//     FMOD_RESULT result;
//     result = FMOD::Studio::System::create(&m_System);
//     if (result != FMOD_OK)
//         SDL_Log("Failed to create FMOD System:%s", FMOD_ErrorString(result));

//     result = m_System->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
//     if (result != FMOD_OK)
//         SDL_Log("failed to initialize FMOD system:%s", FMOD_ErrorString(result));

//     m_System->getCoreSystem(&m_CoreSystem);

//     Loadbank("Assets/Master Bank.strings.bank");
//     Loadbank("Assets/Master Bank.bank");
// }

// AudioSystem::~AudioSystem()
// {
//     m_System->release();
// }

// void AudioSystem::Update(float deltaTime)
// {
//     std::vector<uint32_t> done;
//     for (const auto &iter : m_EventInstances)
//     {
//         FMOD::Studio::EventInstance *eventInstance = iter.second;
//         FMOD_STUDIO_PLAYBACK_STATE state;

//         eventInstance->getPlaybackState(&state);

//         if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
//         {
//             eventInstance->release();
//             done.emplace_back(iter.first);
//         }

//         for (auto id : done)
//             m_EventInstances.erase(id);
//     }

//     m_System->update();
// }

// void AudioSystem::Loadbank(const std::string &name)
// {
//     //�����ظ���ȡ
//     if (m_Banks.find(name) != m_Banks.end())
//         return;

//     FMOD::Studio::Bank *bank = nullptr;
//     FMOD_RESULT result = m_System->loadBankFile(name.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);

//     if (result == FMOD_OK)
//     {
//         //��ȡ�洢����¼�����
//         m_Banks.emplace(name, bank);
//         bank->loadSampleData();
//         int32_t numEventDescriptions = 0;
//         bank->getEventCount(&numEventDescriptions);
//         if (numEventDescriptions > 0)
//         {
//             std::vector<FMOD::Studio::EventDescription *> eventDescriptions(numEventDescriptions);
//             bank->getEventList(eventDescriptions.data(), numEventDescriptions, &numEventDescriptions);
//             char eventDescriptionName[512];
//             for (int32_t i = 0; i < numEventDescriptions; ++i)
//             {
//                 FMOD::Studio::EventDescription *eventDescription = eventDescriptions[i];
//                 eventDescription->getPath(eventDescriptionName, 512, nullptr);
//                 m_EventDescriptions.emplace(eventDescriptionName, eventDescription);
//             }
//         }
//         //��ȡ�洢�������
//         int32_t numBuses = 0;
//         bank->getBusCount(&numBuses);
//         if (numBuses > 0)
//         {
//             std::vector<FMOD::Studio::Bus *> buses(numBuses);
//             bank->getBusList(buses.data(), numBuses, &numBuses);
//             char busName[512];
//             for (int32_t i = 0; i < numBuses; ++i)
//             {
//                 FMOD::Studio::Bus *bus = buses[i];
//                 bus->getPath(busName, 512, nullptr);
//                 m_Buses.emplace(busName, bus);
//             }
//         }
//     }
// }

// void AudioSystem::UnLoadBank(const std::string &name)
// {
//     auto iter = m_Banks.find(name);
//     if (iter != m_Banks.end())
//         return;

//     FMOD::Studio::Bank *bank = iter->second;

//     int32_t numEvents = 0;
//     bank->getEventCount(&numEvents);

//     if (numEvents > 0)
//     {
//         std::vector<FMOD::Studio::EventDescription *> eventDescriptions(numEvents);
//         bank->getEventList(eventDescriptions.data(), numEvents, &numEvents);
//         char eventName[512];
//         for (int32_t i = 0; i < numEvents; ++i)
//         {
//             FMOD::Studio::EventDescription *eventDescription = eventDescriptions[i];
//             eventDescription->getPath(eventName, 512, nullptr);
//             auto eventi = m_EventDescriptions.find(eventName);
//             if (eventi != m_EventDescriptions.end())
//                 m_EventDescriptions.erase(eventi);
//         }
//     }

//     int32_t numBuses = 0;
//     bank->getBusCount(&numBuses);
//     if (numBuses > 0)
//     {
//         std::vector<FMOD::Studio::Bus *> buses(numBuses);
//         bank->getBusList(buses.data(), numBuses, &numBuses);
//         char busName[512];
//         for (int32_t i = 0; i < numBuses; ++i)
//         {
//             FMOD::Studio::Bus *bus = buses[i];
//             bus->getPath(busName, 512, nullptr);
//             auto busi = m_Buses.find(busName);
//             if (busi != m_Buses.end())
//                 m_Buses.erase(busi);
//         }
//     }

//     bank->unloadSampleData();
//     bank->unload();
//     m_Banks.erase(iter);
// }

// void AudioSystem::UnloadAllBank()
// {
//     for (const auto &iter : m_Banks)
//     {
//         iter.second->unloadSampleData();
//         iter.second->unload();
//     }

//     m_Banks.clear();
//     m_EventDescriptions.clear();
// }

// void AudioSystem::SetBusVolume(const std::string &name, float value)
// {
//     auto busIter = m_Buses.find(name);
//     if (busIter != m_Buses.end())
//         busIter->second->setVolume(value);
// }

// float AudioSystem::GetBusVolume(const std::string &name) const
// {
//     float busVolume = 0.0f;
//     auto busIter = m_Buses.find(name);
//     if (busIter != m_Buses.end())
//         busIter->second->getVolume(&busVolume);
//     return busVolume;
// }

// void AudioSystem::SetBusPaused(const std::string &name, bool isPaused)
// {
//     auto busIter = m_Buses.find(name);
//     if (busIter != m_Buses.end())
//         busIter->second->setPaused(isPaused);
// }

// bool AudioSystem::GetBusPaused(const std::string &name) const
// {
//     bool isPaused = false;
//     auto busIter = m_Buses.find(name);
//     if (busIter != m_Buses.end())
//         busIter->second->getPaused(&isPaused);
//     return isPaused;
// }

// AudioEvent *AudioSystem::PlayEvent(const std::string &name)
// {
//     uint32_t retID = 0;
//     auto iter = m_EventDescriptions.find(name);
//     if (iter != m_EventDescriptions.end())
//     {
//         FMOD::Studio::EventInstance *eventInstance = nullptr;
//         iter->second->createInstance(&eventInstance);
//         if (eventInstance)
//         {
//             eventInstance->start();

//             ++m_NextID;
//             retID = m_NextID;

//             m_EventInstances.emplace(retID, eventInstance);
//         }
//     }
//     return new AudioEvent(this, retID);
// }

// void AudioSystem::SetListener(const Matrix4 &viewMatrix)
// {
//     Matrix4 invView = Matrix4::Transpose(Matrix4::Invert(viewMatrix));
//     FMOD_3D_ATTRIBUTES listener;
//     listener.position = ToFMODVector3(Vector3(invView.mat[12], invView.mat[13], invView.mat[14]));
//     listener.forward = ToFMODVector3(Vector3(invView.mat[2], invView.mat[6], invView.mat[10]));
//     listener.up = ToFMODVector3(Vector3(invView.mat[1], invView.mat[5], invView.mat[9]));
//     listener.velocity = {0.0f, 0.0f, 0.0f};
//     m_System->setListenerAttributes(0, &listener);
// }

// FMOD::Studio::EventInstance *AudioSystem::GetEventInstance(uint32_t eventID)
// {
//     auto iter = m_EventInstances.find(eventID);
//     if (iter != m_EventInstances.end())
//         return iter->second;
//     return nullptr;
// }

// FMOD_VECTOR ToFMODVector3(const Vector3 &vec3)
// {
//     FMOD_VECTOR vec;
//     vec.x = vec3.x;
//     vec.y = vec3.y;
//     vec.z = -vec3.z;
//     return vec;
// }