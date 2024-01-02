#ifndef H_VOICE_CHAT
#define H_VOICE_CHAT

#include <iostream>
#include <portaudio.h>

#include "dataType.h"
#include "log.h"
#include "config.h"

namespace FluffyMultiplayer
{
  class VoiceChat
  {
  private:
    FluffyMultiplayer::Log log;
    bool voiceChatOff;
    PaStream* microphone_stream;
    PaStream* speaker_stream;

    PaStreamParameters* inputParameters;
    PaStreamParameters* outputParameters;

    FluffyMultiplayer::SocketReceiveData* receivedVoiceList;
    FluffyMultiplayer::SocketSendData* sendVoiceList;


  public:
    void init(bool mic)
    {
      voiceChatOff = mic;

      //voice
      Pa_Initialize();

      PaStreamParameters inputParameters;
      inputParameters.device = Pa_GetDefaultInputDevice();  // Use the default input device
      inputParameters.channelCount = 1;
      inputParameters.sampleFormat = paFloat32;
      inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency;
      inputParameters.hostApiSpecificStreamInfo = nullptr;
    }

    void printDevices()
    {
      // Get the index of the default input device
          int defaultInputDevice = Pa_GetDefaultInputDevice();
          if (defaultInputDevice == paNoDevice)
          {
              std::cerr << "No default input device found." << std::endl;
              Pa_Terminate();
              return 1;
          }

          // Get the name of the default input device
          const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(defaultInputDevice);
          std::string inputDeviceName = deviceInfo->name;
          std::cout << "Current input device: " << inputDeviceName << std::endl;

    }

    void setInput(int indexDevice)
    {

    }

    void setOuput(int indexDevice)
    {

    }

    void run()
    {
      PaError err = Pa_OpenStream(&microphone_stream, &inputParameters, nullptr, SAMPLE_RATE, FRAMES_PER_BUFFER, paNoFlag, send_voice, nullptr);
      if (err != paNoError)
      {
          std::cerr << "Error opening PortAudio input stream: " << Pa_GetErrorText(err) << std::endl;
          Pa_Terminate();
          return 1;
      }


      Pa_OpenDefaultStream(&speaker_stream, 0, 1, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, receive_voice, nullptr);


      Pa_StartStream(microphone_stream);
      Pa_StartStream(speaker_stream);
    }


    void close()
    {
      // Pa_Terminate();
      Pa_StopStream(microphone_stream);
      Pa_StopStream(speaker_stream);
    }



    static int send_voice(const void* inputBuffer, void* outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void* userData)
    {
          // Cast the input buffer to the desired format
          const float* in = static_cast<const float*>(inputBuffer);

          boost::asio::ip::udp::endpoint udpEndpoint(boost::asio::ip::address::from_string(server_ip), server_voice_port);

          // Send the audio data to the server
          if(!voiceChatOff)
            sendVoiceList.push()...
            // socket_voice.send_to(boost::asio::buffer(in, sizeof(float) * framesPerBuffer), udpEndpoint);
        return paContinue;
    }


    static int receive_voice(const void* inputBuffer, void* outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void* userData)
    {
          // Cast the output buffer to the desired format
          float* out = static_cast<float*>(outputBuffer);

          // Receive audio data from client
          boost::array<float, FRAMES_PER_BUFFER> recvBuffer;
          boost::asio::ip::udp::endpoint senderEndpoint;
          if(!voiceChatOff)
            receivedVoiceList.front()...
            // socket_voice.receive_from(boost::asio::buffer(recvBuffer), senderEndpoint);
          // for(int i=0;i<=99;i++)
            // std::cout << recvBuffer[i] << " ";

          // Copy received audio data to the output buffer
          std::copy(recvBuffer.begin(), recvBuffer.end(), out);

        return paContinue;
    }
  };
}
#endif
