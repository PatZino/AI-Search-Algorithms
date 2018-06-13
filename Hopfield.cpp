#include <bits/stdc++.h>


using namespace std;

int main (int argc, char *argv[])
{
    cout<<"The Hopfield Network: \n\n";
    srand(time(0)); // use current time to seed random number generator
    int n,i,j,k,addition, errorPercentage;
    
    cout << "Enter size of the input state vector: ";
    cin >> n;
    
    cout<<"Input State: ";
	//The maximum number of fundamental memories that can be stored in the n-neuron
	//recurrent network is limited by 0.15n
   
    int m=static_cast<int>(0.15f*n); // number of patterns
	int* pattern=new int[m*n];
    for(j=0;j<m;j++)    
    {
        for(i=0;i<n;i++) 
        {
            pattern[j*n+i]=rand()%2;
            cout<<pattern[j*n+i];
        }
        cout<<endl;
    }
    cout<<endl;

    //Weight Matrix
    int* weightMatrix=new int[n*n];
    for(j=0;j<n;j++)
        for(i=j;i<n;i++)
            if(i==j)
               weightMatrix[j*n+i]=0;
            else
            {
                addition=0;
                for(k=0;k<m;k++)
                    addition+=(pattern[k*n+i]*2-1)*(pattern[k*n+j]*2-1);
     		        weightMatrix[j*n+i]=addition;
                    weightMatrix[i*n+j]=addition;
            }

    
    cout<<"\nWeight Matrix: \n\n";
    for(j=0;j<n;j++)
    {
        for(i=0;i<n;i++)
    	    cout << setw(3) << weightMatrix[j*n+i];
            cout<<endl;
    }
    cout<<endl;

    cout<<"Testing: \n\n";
    // Randomly pick one of the training patterns
    int patternPicked=rand()%m;
    cout<<"Test picked pattern:\n\n";
    for(i=0;i<n;i++)
    {
        cout<<pattern[patternPicked*n+i];
    }
    cout<<"\n\n";

	//Generating probe vector for retrieval
    //Enter error percentage for probe vector
    cout << "Enter error percentage for probe vector: ";
    cin >> errorPercentage;
    
    
    cout<<"\n\nInitial network state: \n\n";
    cout<<errorPercentage<<"% error added: ";
    int* neuron=new int[n];     
    int* neuronPreviousState=new int[n]; 
    for(i=0;i<n;i++)
    {
        neuron[i]=pattern[patternPicked*n+i];
        if(rand()%100<errorPercentage) neuron[i]=1-neuron[i];
        cout<<neuron[i];
        neuronPreviousState[i]=neuron[i]; 
    }
    cout<<"\n\n";

    //exit the loop if network stays stable, it depicts convergence
    int stable=0; 

    // counter is looped to stop the network when it begins to move in cycles or it becomes disorganized
    int counter=0;

    while(stable<100 && counter<500) 
    {

        //updating the network
        for(k=0;k<n;k++)
        {
        	
            // Randomly select a neuron and update its value
            j=rand()%n;
            addition=0;
            for(i=0;i<n;i++)
                if(i!=j)
                    addition+=neuron[i]*weightMatrix[j*n+i];
            if(addition>=0)
                neuron[j]=1;
            else
                neuron[j]=0;
        }

        bool altered=false;
        for(k=0;k<n;k++)
            if(neuron[k]!=neuronPreviousState[k])
            {
                altered=true;
                break;
            }
        if(altered==false)
            stable++;
        else
            stable=0;

        //previous network state updated
        for(k=0;k<n;k++)
            neuronPreviousState[k]=neuron[k];

        counter++;
    }

    if(stable>=100)
    {
        cout<<"Converged state: ";
        for(i=0;i<n;i++)
            cout<<neuron[i];
        cout<<"\n\n";

        int numberOfDifferences=0; 
        for(i=0;i<n;i++)
            if(neuron[i]!=pattern[patternPicked*n+i])
                numberOfDifferences++;
        cout<<"Convergence error percentage:"<<100*numberOfDifferences/n<<endl;
    }
    else
        cout<<"Set convergence limit not reached\n";

    delete []pattern;
    delete []weightMatrix;
    delete []neuron;
    delete []neuronPreviousState;

    return 0;
}
