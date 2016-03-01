class ApplicationBase {

protected:
    const CommandLine& cmd;
    const unsigned count;
    const unsigned iterations;
    bool initialized;

    std::unique_ptr<uint8_t> input;
    std::unique_ptr<uint8_t> output;
public:
    ApplicationBase(const CommandLine& c)
        : cmd(c)
        , count(64*1024*1024)
        , iterations(10)
        , initialized(false) {}

protected:
    void initialize() {

        if (initialized) {
            return;
        }

        base64::scalar::initialize();

        input.reset (new uint8_t[get_input_size()]);
        output.reset(new uint8_t[get_output_size()]);

        printf("input size: %lu\n", get_input_size());

        fill_input();

        initialized = true;
    }

    size_t get_input_size() const {
        return count;
    }

    size_t get_output_size() const {
        return (3*count)/4;
    }

    void fill_input() {
        for (unsigned i=0; i < get_input_size(); i++) {
            const uint8_t idx = i * 71;
            input.get()[i] = base64::lookup[idx % 64];
        }
    }

    void clear_output() {
        memset(output.get(), 0, get_output_size());
    }
};