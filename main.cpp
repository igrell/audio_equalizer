#include <iostream>
#include <utility>
#include "fstream"
#include "vector"

using std::ifstream, std::cout, std::string, std::vector;

struct Audio {
    size_t sampleRate;
    vector<long long> audioData;

    Audio(const size_t _sampleRate, vector<long long> _audioData) :
    sampleRate(_sampleRate), audioData(std::move(_audioData)) {}

    [[nodiscard]] size_t length() const { return audioData.size() / sampleRate; }
};

std::ostream& operator<<(std::ostream& ostream, const Audio& audio) {
    ostream << "Sample rate [Hz]: " << audio.sampleRate << "\n";
    ostream << "No. of samples: " << audio.audioData.size() << "\n";
    ostream << "Audio time [s]: " << audio.length() << "\n";
    return ostream;
}

Audio parseAudiofile(const string& filename) {
    ifstream file;
    file.open(filename, ifstream::in);

    size_t sampleRate;

    string tmp;
    std::getline(file, tmp);
    sampleRate = stoi(tmp);
    vector<long long> audioData;
    while(std::getline(file, tmp)) audioData.emplace_back(stoi(tmp));
    file.close();
    return {sampleRate, audioData};
}

int main() {
    Audio audio = parseAudiofile("../data.txt");
    cout << audio;
    return 0;
}
