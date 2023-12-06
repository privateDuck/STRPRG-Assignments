#include <stdio.h>
#include <time.h>
#define COIN_TYPE_COUNT 4
#define STAMP_TYPE_COUNT 3

static const int accepted_coins[COIN_TYPE_COUNT] = {5, 10, 25, 50};
static const int stamp_types[STAMP_TYPE_COUNT] = {10, 15, 25};

struct MachineStateStruct{
    int coins_available[COIN_TYPE_COUNT];
    int stamps_available[STAMP_TYPE_COUNT];
} typedef MachineState;

struct RequestInfoStruct{
    int coin;
    int stamp;
    int change;
    int has_error;
} typedef RequestInfo;

/// Summery : This function checks if a input coin is a valid coin
int CheckValidCoin(int coin){
    for(int i=0; i<COIN_TYPE_COUNT; i++){
        if(coin == accepted_coins[i])
            return i;
    }
    return -1;
}

/// Summery : This function checks if a input stamp is a valid stamp
int CheckValidStamp(int stamp){
    for(int i=0; i<STAMP_TYPE_COUNT; i++){
        if(stamp == stamp_types[i])
            return i;
    }
    return -1;
}

/// Summery : This function outputs change, if any
/// Returns : whether or not machine has coins to return
int ReturnChange(MachineState* const state, int change){
    switch(change){
        case 10:
            if(state->coins_available[1] > 0){
                state->coins_available[1]--;
                puts("\nReturned 10 Rupees.");
            }
            else return 0;
            break;
        case 15:
            if(state->coins_available[1] > 0 && state->coins_available[0] > 0){
                state->coins_available[1]--;
                state->coins_available[0]--;
                puts("\nReturned 5 and 10 Rupees.");
            }
            else return 0;
            break;
        case 25:
            if(state->coins_available[2] > 0)
            {
                state->coins_available[2]--;
                puts("\nReturned 25 Rupees.");
            }
            else return 0;
            break;
        case 35:
            if(state->coins_available[1] > 0 && state->coins_available[2] > 0){
                state->coins_available[1]--;
                state->coins_available[2]--;
                puts("\nReturned 25 and 10 Rupees.");
            }
            else return 0;
            break;
        case 40:
            if(state->coins_available[0] > 0 && state->coins_available[1] > 0 && state->coins_available[2] > 0){
                state->coins_available[0]--;
                state->coins_available[1]--;
                state->coins_available[2]--;
                puts("\nReturned 25, 10 and 5 Rupees.");
            }
            else return 0;
            break;
        default:
            puts("\nUndefined Behaviour...");
            break;
    }
    return 1;
}

/// Summery : This function handles user inputs
/// Returns : Information about the user request
RequestInfo InsertCoin(){
    RequestInfo ri;
    int inserted_coin, requested_stamp;

    printf("Please Insert a Coin... \n");
    scanf("%d", &inserted_coin);
    int coin = CheckValidCoin(inserted_coin);

    if(coin < 0){
        ri.has_error = 1;
        printf("\nIllegal Coin...\n");
        return ri;
    }

    printf("\nEnter the stamp value...\n");
    scanf("%d", &requested_stamp);
    int stamp = CheckValidStamp(requested_stamp);

    if(stamp < 0){
       ri.has_error = 1;
       printf("\nNo Such Stamp Available...\n");
       return ri;
    }

    if(inserted_coin - requested_stamp < 0){
        printf("\nInsufficient Amount Tendered...\n");
        ri.has_error = -1;
        return ri;
    }

    ri.has_error = 0;
    ri.stamp = stamp;
    ri.coin = coin;
    ri.change = inserted_coin - requested_stamp;

    return ri;
}

void PerformTransaction(MachineState* state, RequestInfo* ri){
    state->coins_available[ri->coin]++;
    state->stamps_available[ri->stamp]--;
    printf("\nStamp Dispensed (%d Rupee Stamp).\n", stamp_types[ri->stamp]);
    puts("\nCoins Available: ");

    for(int i = 0; i<COIN_TYPE_COUNT; i++)
        printf("  Rs %d : %d \n", accepted_coins[i], state->coins_available[i]);
    puts("\nStamps Available: ");
    for(int i = 0; i<STAMP_TYPE_COUNT; i++)
        printf("  Rs %d : %d \n", stamp_types[i], state->stamps_available[i]);
}

// Entry point of the application
int main2(void){
    // ---- Initialization ---- //
    MachineState state;

    // No of 5 rupee coins
    state.coins_available[0] = 4;
    // No of 10 rupee coins
    state.coins_available[1] = 5;
    // No of 25 rupee coins
    state.coins_available[2] = 5;
    // No of 50 rupee coins
    state.coins_available[3] = 5;

    // No of 10 rupee stamps
    state.stamps_available[0] = 5;
    // No of 15 rupee stamps
    state.stamps_available[1] = 5;
    // No of 25 rupee stamps
    state.stamps_available[2] = 4;

    // Main program loop
    while(1){
        // Clear the console after every transaction
        system("cls");
        puts("....Stamp Vending Machine....\n\n");

        // Handles user inputs
        RequestInfo ri = InsertCoin();

        if(!ri.has_error){
            // checks if the requested stamp is available
            if(state.stamps_available[ri.stamp] == 0) {
                puts("\nRequested Stamp Not Available.");
                printf("Returning Inserted Coin: (%d Rupees)\n", accepted_coins[ri.coin]);
            }
            // if available we proceed
            else{
                int ch = ri.change;
                // if we have to return change we have to check,
                // if we have enough coins to return
                if(ch > 0){
                    // ReturnChange function outputs change if we have enough coins and
                    // returns whether or not we have enough coins
                    int has_change = ReturnChange(&state, ch);
                    if(has_change){
                        // Now we accept the users payment and dispense the requested stamp
                        PerformTransaction(&state, &ri);
                    }
                    else{
                        printf("\nNo change available..\n");
                        printf("Returning Inserted Coin: (%d Rupees)\n", accepted_coins[ri.coin]);
                    }
                }
                // if no change has to be returned, we dont have to care about
                // the internal state of the machine
                else{
                    // Now we accept the users payment and dispense the requested stamp
                    PerformTransaction(&state, &ri);
                }

            }
        }

        puts("\nDo you want to perform another transaction? (y/n) ");
        char close_char = getch();

        // If the user does not want to perform any more transactions,
        // we wait for 2200 milliseconds and exit from the application.
        if(close_char == 'n') {
            puts("\n\n...Thank you for using the Stamp Vending Machine...");
            time_t t = clock();
            while(1){
                if(clock() - t > 2200) break;
            }
            return 0;
        }
        // If the user wants to perform another transaction,
        // we proceed to the next iteration
        else if(close_char == 'y') continue;

        // If the user input an illegal input program returns the error code '-1'
        else return -1;
    }
}

