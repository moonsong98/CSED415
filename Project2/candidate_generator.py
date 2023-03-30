cand = []

def gen(word, pos, len):
    if pos == -1:
        cand.append(word)
        return
    for step in range(0, 26, 1):
        gen(word + chr(ord('a')+step), pos-1, len)


for len in range(3, 7, 1):
    gen('', len - 1, len)

with open('./test_candidate.txt', 'w') as f:
    for word in cand:
        f.write(f'{word}\n')

