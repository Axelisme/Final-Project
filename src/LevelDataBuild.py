# %%
import numpy as np
obj = {
    "Air":0, 
    "Ground":1, 
    "Snake Head":2, 
    "Snake Body":3, 
    "End point":4,
    "Apple":5, 
    "Stone":6,
    "Edge":-1
    }
def map_to_graph(map):
    map_graph = [''.join(
    '██' if j == obj["Ground"] else 
    '  ' if j==obj["Air"] else 
    '░░' if j==obj["Stone"] else 
    '▓▓' if j==obj["Snake Head"] else 
    '▒▒' if j==obj["Snake Body"] else  
    ' ⋄' if j==obj["Apple"] else 
    ' ⊠' if j==obj["End point"] else
    '▞▞' if j==obj["Edge"] else
    '  ' for j in i) + '\n' for i in map1]
    return map_graph
def map_to_string(map):
    map_str = ['\t'.join(
    f'{obj["Ground"]}' if j == obj["Ground"] else 
    f'{obj["Air"]}' if j==obj["Air"] else 
    f'{obj["Stone"]}' if j==obj["Stone"] else 
    f'{obj["Snake Head"]}' if j==obj["Snake Head"] else 
    f'{obj["Snake Body"]}' if j==obj["Snake Body"] else  
    f'{obj["Apple"]}' if j==obj["Apple"] else
    f'{obj["End point"]}' if j==obj["End point"] else 
    f'{obj["Edge"]}' if j==obj["Edge"] else
    '0' for j in i) + '\n' for i in map1]
    return map_str

map1_high, map1_width = 10, 25
map1 = np.zeros([map1_high, map1_width]).astype(int)
map1[1:4,17] = obj["Ground"]
map1[6,10:24] = obj["Ground"]
map1[6,14:17] = obj["Air"]
map1[4,4] = obj["Ground"]
map1[9,24] = obj["Ground"]
map1[5,1:13] = obj["Ground"]
map1[5,6:8] = obj["Air"]
map1[5,11] = obj["Air"]
map1[2,9:14] = obj["Ground"]
map1[2,11] = obj["Air"]
map1[3,[9,12]] = obj["Ground"]
map1[4,12] = obj["Ground"]
map1[0,17] = obj["Stone"]
map1[3,10] = obj["Apple"]
map1[3,18] = obj["Apple"]
map1[7,19] = obj["End point"]
map1[4,1] = obj["Snake Head"]
map1[4,0] = obj["Snake Body"]
map1[5,0] = obj["Snake Body"]
map1[5,0] = obj["Snake Body"]

edge_thick = 6
edge_col = np.full((map1_high,edge_thick),obj["Air"])
edge_row = np.full((edge_thick,map1_width+2*edge_thick),obj["Air"])
map1 = np.concatenate([edge_col, map1], axis=1)
map1 = np.concatenate([map1, edge_col], axis=1)
map1 = np.concatenate([edge_row, map1], axis=0)
map1 = np.concatenate([map1, edge_row], axis=0)
map1[0,:] = map1[-1,:] = map1[:,0] = map1[:,-1] = obj["Edge"]

map1_list = map1.tolist()
map1_graph = map_to_graph(map1)
map1_str = map_to_string(map1)

level1 = {
    "background": ['/data/image/background1'],
    "music": ['/data/music/music1'],
    "sound": ['/data/sound/sound1-1','/data/sound/sound1-2'],
    "map":[map1.shape, map1_str, map1_graph],
    "snake":[
        '11 6',
        '10 6',
        '10 7',
    ],
    "stone":[
        '6 23'
        ]
}

level_set = [level1]
with open('../data/level/L1','w') as fh:
    for level in level_set:
        fh.write('\n'.join(
            [
                "1background", str(len(level["background"])),*level["background"],'',
                "2music", str(len(level["music"])),*level["music"],'',
                "3snake", str(len(level["snake"])), *level["snake"],'',
                "4stone", str(len(level["stone"])), *level["stone"],'',
                "5map", f'{level["map"][0][0]} {level["map"][0][1]}',''
            ]
        )+'\n')
        fh.writelines([
            *level["map"][1], *level["map"][2]
        ])