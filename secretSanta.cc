#include<iostream>
#include<string>
#include <stdlib.h> 
#include <time.h>

using namespace std;

int main(){
beginning:
    const int n_Santas = 7;
    const string Santas[n_Santas] = {"", "", "", "", "", "", ""}; //Since the default is 7, every subsequent array has 7 values. If you need more add more.
    const string inValidPairs[7][4] = {{}, {}, {}, {}, {}, {}, {}}; //Assign filtered pairing to remove them from selection pool.
    string Gifter[n_Santas];
    string Giftees[n_Santas][n_Santas - 1];
    string cleanGiftees[n_Santas][n_Santas-1];
    string alreadyPicked[n_Santas];
    string finalGiftee[n_Santas];
    bool toShift = false;
    int toShiftAmount = 0;
    int failCounter = 0;

    string account_sid ="";
    string auth_token= "";
    string fullCommand = "";

    //Type in the phone numbers directly corrolated to above Santas.
    //Example: "+12120001111"
    string phoneNumbers[n_Santas] = {"+1", "+1", "+1", "+1", "+1", "+1", "+1"};
    string sendFrom = ""; //Type in the phone number associated with the twillio account.
    const char * command = "";

    //Count row size:
    int count[n_Santas] = {0,0,0,0,0,0,0};

    //setting Random Seed time
    srand(time(NULL));

    for (int i = 0; i < n_Santas; i++){
        Gifter[i] = Santas[i];
        // cout << Gifter[i] << endl;
        for(int j = 0; j < n_Santas; j++){
            // cout << Gifter[i] << " " << Santas[j] << endl;
            // if((Gifter[i] == Santas[j]) && !toShift){
            //     cout << "\tMUST TAKE OUT THIS POSSIBILITY" << endl;
            // }



            if((Gifter[i] != Santas[j]) && !toShift){
               Giftees[i][j] = Santas[j];
            //    cout << " (" << Giftees[i][j];
            //    cout << " OFF)";
            }
            else if(toShift){
                Giftees[i][j-1] = Santas[j];
                // cout << " " << Giftees[i][j];
            }
            else{
                toShift = true;
            }
        }
        toShift = false;
        // cout << endl;
    }

    //Clean inValid possibilties:
    toShift = false;
    for (int i = 0; i < n_Santas; i++){
        for (int j = 0; j < n_Santas-1; j++){
            for(int k = 0; k < (sizeof(inValidPairs[i])/sizeof(inValidPairs[i][0])); k++){
                cout << endl << "Gifter: " << Gifter[i] << endl;
                cout << "Check Cleaning: Regular Giftee " << Giftees[i][j] << " DOES IT MATCH WITH? " << inValidPairs[i][k] << endl;
                if(Giftees[i][j] == inValidPairs[i][k]){
                    cout << "\tMATCH" << endl;
                    toShiftAmount++;
                    toShift = false;
                    break;
                }//RESET toShiftAmount
                else if(Giftees[i][j] != inValidPairs[i][k]){
                    cout << "\tNo Match" << endl;
                    toShift = true;
                    // cout << "No issue: " << Giftees[i][j] << " and " << inValidPairs[i][k] << endl;
                }

            }
            if(toShift){
                cout << endl << "Saving the check! " << Giftees[i][j] << endl;
                cleanGiftees[i][j - toShiftAmount] = Giftees[i][j];
                toShift = false;
            }
            else {
                cout << endl << "Not saving the above person!" << endl;
            }
            
            
        }
        toShift = false;
        toShiftAmount = 0;
    }

    //Randomizing and Final Pickings
    
    for(int i = 0; i < n_Santas; i++){
        for(int j = 0; j < n_Santas - 1; j++){
            if(cleanGiftees[i][j] != ""){
                count[i]++;
            }
        }
    }
    // for(int i = 0; i < n_Santas; i++){
    //     cout << "Gifter " << Gifter[i] << " has " << count[i] << " possibilities." << endl;
    // }
    int randomPick = 0;
    toShift = false;
    toShiftAmount = 0;
    for(int i = 0; i < n_Santas; i++){
retry:
        randomPick = rand() % count[i];
        for(int j = 0; j < n_Santas; j++){
            if(alreadyPicked[j] == cleanGiftees[i][randomPick]){
                cout << "This person has already been picked... picking someone else..." << endl; 
                failCounter++;
                if(failCounter >= 100){
                    goto beginning;
                }
                goto retry;
            }
        }
        finalGiftee[i] = cleanGiftees[i][randomPick];
        alreadyPicked[i] = finalGiftee[i];

    }
    
        // for(int o = 0; o < n_Santas; o++){
        //     for(int k = 0; k < count[o]; k++){
        //         for(int l = 0; l < n_Santas; l++){
        //             if(cleanGiftees[o][k] == stillCanBePicked[l]){
        //                 toShift = false;
        //             }
        //             else{
                        
        //             }
        //         }
        //     }
        // }

    //Print Gifters and Giftees

    for(int i = 0; i < n_Santas; i++){
        cout << "Gifter: " << Gifter[i] << "\n\tPotential Giftees:";
        for(int j = 0; j < n_Santas-1; j++){
            cout << " " << Giftees[i][j];
        }
        cout << endl;
    }
    cout << endl << endl << "----------------------------------------------------" << endl << endl;

    for(int i = 0; i < n_Santas; i++){
        cout << "Gifter: " << Gifter[i] << "\n\tCleaned Potential Giftees:";
        for(int j = 0; j < n_Santas-1; j++){
            cout << " " << cleanGiftees[i][j];
        }
        cout << endl;
    }

    cout << endl << endl << "----------------------------------------------------" << endl << endl;



    // for(int i = 0; i < n_Santas; i++){
    //     cout << "Gifter: " << Gifter[i] << " is the Santa for: " << finalGiftee[i] << endl;
    // }
    //Re_Enable Here
    

    

    for(int i = 0; i < n_Santas; i++){
        // fullCommand = "./twilio_cpp_demo/bin/cpp_demo -a " + account_sid + " -s " + auth_token + " -t \""+ phoneNumbers[i] +"\" -f \"+18889974616\" -m \"-----THE BELOW MESSAGE IS YOUR OFFICIAL GIFTEE-----\"";
        // command = fullCommand.c_str();
        // system(command);
        
        fullCommand = "./twilio_cpp_demo/bin/cpp_demo -a " + account_sid + " -s " + auth_token + " -t \""+ phoneNumbers[i] +"\" -f \""+ sendFrom +"\" -m \"Hello "+ Gifter[i] + "\n\t You are the secret santa of: " + finalGiftee[i] + "\"";
        command = fullCommand.c_str();
        // cout << "output command: " << fullCommand << endl;
        system(command);

        fullCommand = "./twilio_cpp_demo/bin/cpp_demo -a " + account_sid + " -s " + auth_token + " -t \""+ phoneNumbers[i] +"\" -f \"" + sendFrom + "\" -m \"Happy Holidays! Have fun being Santa!!!!\"";
        command = fullCommand.c_str();
        system(command);
    }

    return 0;
}
