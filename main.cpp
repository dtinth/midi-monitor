#include <RtMidi.h>
#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <memory>

using namespace std;

int main()
{
    std::vector<std::unique_ptr<RtMidiIn>> inputs;
    vector<unsigned char> message;
    try
    {
        {
            RtMidiIn probe;
            unsigned int nPorts = probe.getPortCount();
            for (unsigned int i = 0; i < nPorts; i++)
            {
                string portName = probe.getPortName(i);
                cout << "port\t" << i << "\t" << portName << endl;
                auto input = make_unique<RtMidiIn>();
                input->openPort(i);
                inputs.push_back(move(input));
            }
        }
        for (;;)
        {
            bool found = false;
            for (auto &input : inputs)
            {
                input->getMessage(&message);
                if (message.size() > 0)
                {
                    cout << "message";
                    for (auto b : message)
                    {
                        cout << "\t" << (int)b;
                    }
                    cout << endl;
                    found = true;
                }
            }
            if (!found)
            {
                usleep(33333);
            }
        }
    }
    catch (RtMidiError &error)
    {
        cout << "RtMidiError\t" << error.getMessage() << endl;
    }
    return 0;
}