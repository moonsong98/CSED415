import argparse
import random
import mmh3

def main(args):
    # Extract Arguments
    filename_dictionary = args.dict
    filename_candidate = args.cand
    num_hash_functions = args.k
    num_hash_values = args.n

    # Extract File
    dict_list = []
    cand_list = []

    with open(filename_dictionary, 'r') as f:
        dict_list = f.readlines()
        dict_list[:] = [e.strip() for e in dict_list]

    with open(filename_candidate, 'r') as f:
        cand_list = f.readlines()
        cand_list[:] = [e.strip() for e in cand_list]

    # Generate Seeds
    seeds = []
    for _ in range(0, num_hash_functions, 1):
        seeds.append(random.randint(0, 100))

    global_map = [0] * num_hash_values    
    
    # Generate a Global Map
    for key in dict_list:
        for seed in seeds:
            global_map[mmh3.hash(key, seed)%num_hash_values] = 1
    

    num_fp = 0
    num_cand = len(cand_list)
    cand_result = []

    # Test 
    for cand in cand_list:
        cnt = 0
        for seed in seeds:
            cnt += global_map[mmh3.hash(cand, seed)%num_hash_values]
        if cnt == num_hash_functions and cand not in dict_list:
            num_fp += 1
        cand_result.append(1 if cnt == num_hash_functions else 0)

    with open('./test_result.txt', 'w') as f:
        for i, seed in enumerate(seeds):
            f.write(f'SEED #{i+1}: {seed}\n')
        f.write(f'#FP: {num_fp}, #cand: {num_cand}, proportion: {num_fp / num_cand}')

    with open('./Bloomchecked.txt', 'w') as f:
        for i, e in enumerate(cand_list):
            f.write(f'{e} {cand_result[i]}\n')



if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--dict', type = str)
    parser.add_argument('--cand', type = str)
    parser.add_argument('--k', type=int, default=3)
    parser.add_argument('--n', type=int, default=8192)

    args = parser.parse_args()
    main(args)
