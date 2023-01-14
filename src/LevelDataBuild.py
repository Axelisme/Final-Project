# %%
import numpy as np
obj = {
    "Air":0, 
    "Block":1, 
    "Snake Head":2, 
    "Snake Body":3, 
    "End point":4,
    "Apple":5, 
    "Stone":6
    }
def map_to_graph(map):
    map_graph = [''.join(
    '██' if j == obj["Block"] else 
    '  ' if j==obj["Air"] else 
    '░░' if j==obj["Stone"] else 
    '▓▓' if j==obj["Snake Head"] else 
    '▒▒' if j==obj["Snake Body"] else  
    ' ⋄' if j==obj["Apple"] else 
    ' ⊠' if j==obj["End point"] else
    '  ' for j in i) + '\n' for i in map1]
    return map_graph
def map_to_string(map):
    map_str = ['\t'.join(
    f'{obj["Block"]}' if j == obj["Block"] else 
    f'{obj["Air"]}' if j==obj["Air"] else 
    f'{obj["Stone"]}' if j==obj["Stone"] else 
    f'{obj["Snake Head"]}' if j==obj["Snake Head"] else 
    f'{obj["Snake Body"]}' if j==obj["Snake Body"] else  
    f'{obj["Apple"]}' if j==obj["Apple"] else
    f'{obj["End point"]}' if j==obj["End point"] else 
    '0' for j in i) + '\n' for i in map1]
    return map_str

map1 = np.zeros([10,25]).astype(int)
map1[1:4,17] = obj["Block"]
map1[6,10:24] = obj["Block"]
map1[6,14:17] = obj["Air"]
map1[4,4] = obj["Block"]
map1[9,24] = obj["Block"]
map1[5,1:13] = obj["Block"]
map1[5,6:8] = obj["Air"]
map1[5,11] = obj["Air"]
map1[2,9:14] = obj["Block"]
map1[2,11] = obj["Air"]
map1[3,[9,12]] = obj["Block"]
map1[4,12] = obj["Block"]
map1[0,17] = obj["Stone"]
map1[3,10] = obj["Apple"]
map1[3,18] = obj["Apple"]
map1[7,19] = obj["End point"]
map1[4,1] = obj["Snake Head"]
map1[4,0] = obj["Snake Body"]
map1[5,0] = obj["Snake Body"]
# map1_shape = map1.shape
map1_list = map1.tolist()
map1_graph = map_to_graph(map1)
map1_str = map_to_string(map1)

level1 = {
    "background": '/data/image/background1',
    "music": '/data/music/music1',
    "sound": ['/data/sound/sound1-1','/data/sound/sound1-2'],
    "map":[map1.shape, map1_str, map1_graph],
    "snake":[
        '4 1',
        '4,0',
        '5,1',
    ]
}

level_set = [level1]
with open('../data/level/L1','w') as fh:
    for level in level_set:
        fh.write('\n'.join(
            [
                "background", level["background"],
                "music", level["music"],
                "sound", *level["sound"],
                "snake", str(len(level["snake"])), *level["snake"],
                "map", f'{level["map"][0][0]} {level["map"][0][1]}'
            ]
        )+'\n')
        fh.writelines([
            *level["map"][1], *level["map"][2]
        ])