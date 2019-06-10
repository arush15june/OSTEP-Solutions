import subprocess
import json
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

SAMPLES = 300000000

if __name__ == "__main__":
    data_dict = {
        'pages': [],
        'access': []
    }
    
    # """ COMMENT FROM BELOW """
    for i in range(1, 20000, 64):
        output = subprocess.check_output(f'./tlb {i} {SAMPLES}', stderr=subprocess.STDOUT, shell=True)
        data_dict['pages'].append(i)
        data_dict['access'].append(float(output))
        print(i, float(output), f'{float(output)/(SAMPLES)}ns')

    with open('data.json', 'w') as f:
        f.write(json.dumps(data_dict))
    
    df = pd.DataFrame(data_dict)
    # """ TILL ABOVE AND UNCOMMENT BELOW """
    # df = pd.read_json('data.json')
    df['access'] = df['access'].apply((lambda x: x/SAMPLES), 1)
    sns.set_style('darkgrid')
    plt.xlabel('Number Of Pages')
    plt.ylabel('Memory Access Time (ns)')
    plt.plot(df['pages'], df['access'])
    plt.show()