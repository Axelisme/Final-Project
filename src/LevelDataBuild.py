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
    "Spike":7,
    "Button":8,
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
    '||' if j==obj["Spike"] else
    ' ▂' if j==obj["Button"] else
    '▞▞' if j==obj["Edge"] else
    '  ' for j in i) + '\n' for i in map]
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
    '0' for j in i) + '\n' for i in map]
    return map_str

def add_edge(map, thick = 7):
    high, width = map.shape
    edge_col = np.full((high,thick),obj["Air"])
    edge_row = np.full((thick,width+2*thick),obj["Air"])
    map = np.concatenate([edge_col, map], axis=1)
    map = np.concatenate([map, edge_col], axis=1)
    map = np.concatenate([edge_row, map], axis=0)
    map = np.concatenate([map, edge_row], axis=0)
    map[0:2,:] = map[-2:,:] = map[:,0:2] = map[:,-2:] = obj["Edge"]
    return map

def write_file(id,level):
    with open(f'../data/level/L{id}','w') as fh:
        fh.write('\n'.join(
            [
                "1background", str(len(level["background"])),*level["background"],'',
                "2music", str(len(level["music"])),*level["music"],'',
                "3snake", str(len(level["snake"])), *level["snake"],'',
                "4stone", str(len(level["stone"])), *level["stone"],'',
                "5button", str(len(level["button"])), *level["button"],'',
                "6map", f'{level["map"][0][0]} {level["map"][0][1]}',''
            ]
        )+'\n')
        fh.writelines([
            *level["map"][1], *level["map"][2]
        ])
    return

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
map1 = add_edge(map1)
map1_list = map1.tolist()
map1_graph = map_to_graph(map1)
map1_str = map_to_string(map1)

level1 = {
    "background": ['/data/image/background1'],
    "music": ['/data/music/music1'],
    "sound": ['/data/sound/sound1-1','/data/sound/sound1-2'],
    "map":[map1.shape, map1_str, map1_graph],
    "snake":[
        '12 7',
        '11 7',
        '11 8',
    ],
    "stone":[
        '7 24'
        ],
    "button":[
    ]
    }

write_file(1,level1)

map2_high, map2_width = 10, 25
map2 = np.zeros([map2_high, map2_width]).astype(int)
map2[3:8,1] = obj["Ground"]
map2[[3,7],2] = obj["Ground"]
map2[1:5,4] = obj["Ground"]
map2[2:4,5] = obj["Ground"]
map2[1:5,4] = obj["Ground"]
map2[6,4:18] = obj["Ground"]
map2[6,[8,16]] = obj["Air"]
map2[3:9,7] = obj["Ground"]
map2[7,9] = obj["Ground"]
map2[8,8:10] = obj["Ground"]
map2[3:5,9] = obj["Ground"]
map2[4,10] = obj["Ground"]
map2[2,13:21] = obj["Ground"]
map2[2,14] = obj["Air"]
map2[3,[15,18]] = obj["Ground"]
map2[3:5,19:21] = obj["Ground"]
map2[7,15:19] = obj["Ground"]
map2[7,21:25] = obj["Ground"]
map2[8,18:23] = obj["Ground"]
map2[6,21:23] = obj["Ground"]
map2[5,17] = obj["Ground"]
map2[4:6,13:15] = obj["Ground"]
map2[[2,5,4,5,5],[9,12,14,19,22]] = obj["Spike"]
map2[[6,5,2],[3,16,12]] = obj["Apple"]
map2[[1,5],[5,15]] = obj["Button"]
map2[6,24] = obj["End point"]
map2[2:4,0] = obj["Snake Body"]
map2[2,1] = obj["Snake Head"]
map2 = add_edge(map2)
map2_list = map2.tolist()
map2_graph = map_to_graph(map2)
map2_str = map_to_string(map2)

level2 = {
    "background": ['/data/image/background2'],
    "music": ['/data/music/music2'],
    "sound": ['/data/sound/sound2-1','/data/sound/sound2-2'],
    "map":[map1.shape, map1_str, map1_graph],
    "snake":[
        '10 7',
        '9 7',
        '9 8',
    ],
    "stone":[
        ],
    "button":[
        '8 12 Short',
        '''12 22 Spike
2
11 21
8 22''',
    ]
    }

write_file(2,level2)