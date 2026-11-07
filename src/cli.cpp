#include "image_processing/cli.hpp"
#include "image_processing/io.hpp"
#include "image_processing/operations.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace image_processing 
{
    namespace 
    {
        int number(const char* s) 
        {
            std::size_t used = 0; 
            int n = std::stoi(s, &used);

            if (s[used] != '\0') throw std::invalid_argument("expected an integer: " + std::string(s));

            return n;
        }

        void usage() 
        {
            std::cout << "Usage:\n  image_processing grayscale INPUT OUTPUT\n  image_processing crop INPUT OUTPUT X Y WIDTH HEIGHT\n  image_processing resize INPUT OUTPUT WIDTH HEIGHT\n";
        }
    }

    int run_cli(int argc, char* argv[]) 
    {
        if (argc < 2 || std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") 
        {
            usage(); 
            return argc < 2 ? 2 : 0; 
        }

        try 
        {
            const std::string command = argv[1];

            const int expected = command == "crop" ? 8 : (command == "resize" ? 6 : 4);

            if (argc != expected) 
            {
                usage(); 
                return 2; 
            }

            Image input = load_image(argv[2]);
            Image output;

            if (command == "grayscale") 
                output = grayscale(input);
            else if (command == "resize") 
                output = resize_nearest(input, number(argv[4]), number(argv[5]));
            else if (command == "crop") 
                output = crop(input, number(argv[4]), number(argv[5]), number(argv[6]), number(argv[7]));
            else 
            {
                usage(); 
                return 2; 
            }

            save_image(output, argv[3]);
            std::cout << "Saved " 
                      << argv[3] 
                      << " (" 
                      << output.width 
                      << "x" 
                      << output.height 
                      << ")\n";

            return 0;
        }
        catch (const std::exception& e) 
        {
            std::cerr << "image_processing: " 
                      << e.what() 
                      << '\n';
            return 1; 
        }
    }
} // namespace image_processing
