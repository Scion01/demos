g++ -I./../../../include/ -I./../../../soundgen/ -D__LINUX_ALSA__ main.cpp ./../../../soundgen/externals/RtMidi/RtMidi.cpp ./../audio/audio.openal.cpp ./../../../soundgen/OpenAL/mxsoundgenopenal.cpp ./../../../soundgen/OpenAL/mxopenalsourcemanager.cpp -o ./../bin/06_Recording ./../../../lib/Linux/modus.a -lopenal -logg -lvorbis -lvorbisfile -lasound -fpermissive
