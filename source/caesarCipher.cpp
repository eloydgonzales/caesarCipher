#include <iostream>
#include <fstream>



char convert(char c, int shift, bool encrypt)
{
    if (!encrypt)
    {
        shift = shift * -1;
    }
    
    if (c >= 97 && c <= 122)
    {
        return char((((c - 97 + shift) % 26) + 26) % 26 + 97);
    }
    else if (c >= 65 && c <= 90)
    {
        return char((((c - 65 + shift) % 26) + 26) % 26 + 65);
    }
    else
    {
        return char(c);
    }
}



// ccipher 
int main(int argc, char* argv[])
{
    // initialize arguments
    std::string mode{argv[1]};
    int shift{atoi(argv[2])};
    std::string source{argv[3]};
    std::string destination{argv[4]};

    std::ifstream inputFile (source);
    std::ofstream outputFile (destination);

    bool encrypt{true};

    if (mode != "encrypt")
    {
        encrypt = false;
    }
    
    if (mode == "brute-force")
    {
        if (inputFile.is_open())
        {
            std::string line;

            for (size_t i = 1; i < 26; i++)
            {
                std::cout << "key=" << i << std::endl;
                while ( getline (inputFile,line) )
                {
                    for ( std::string::iterator it=line.begin(); it!=line.end(); ++it)
                    {
                        std::cout << convert(*it, i, encrypt);
                    }
                    std::cout << std::endl;
                }
                inputFile.clear();
                inputFile.seekg(0, inputFile.beg);
            }
            inputFile.close();
        }
        else std::cout << "Unable to open file";
    }
    else if (inputFile.is_open() && outputFile.is_open())
    {
        std::string line;
        while ( getline (inputFile,line) )
        {
            for ( std::string::iterator it=line.begin(); it!=line.end(); ++it)
            {
                outputFile << convert(*it, shift, encrypt);
            }
            outputFile << std::endl;
        }
        inputFile.close();
        outputFile.close();
    }
    else std::cout << "Unable to open file";

	return 0; 
}
