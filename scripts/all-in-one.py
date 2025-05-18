import os
import sys
import pandas as pd

if len(sys.argv) > 1:
    root_path = sys.argv[1]
else:
    root_path = '..'
case_result = '/case_result.txt'
ref_path = '/win32_cl'
ref_name = 'win32_cl'

folder_list = os.listdir(root_path + '/all-in-one')
print(f'Artifact root path = {root_path}\nCurrent artifact under root path = {folder_list}')

try:
    assert 'win32_cl' in folder_list
except AssertionError:
    print('No result of win32 in file list, exiting...')
    exit()

# read win32_cl as reference result
ref_ans = pd.read_csv(root_path + '/all-in-one' + ref_path + case_result, header=None, names=[f'{ref_name}_dec', f'{ref_name}_hex'])
ref_row, ref_col = ref_ans.shape
total_ans = ref_ans.copy()

for current_folder in folder_list:
    if current_folder == ref_name:
        continue
    current_ans = pd.read_csv(root_path + '/all-in-one/' + current_folder + case_result, header=None, names=[f'{current_folder}_dec', f'{current_folder}_hex'])
    for i in range(ref_row):
        if current_ans.loc[i, f'{current_folder}_hex'] == ref_ans.loc[i, f'{ref_name}_hex']:
            current_ans.loc[i, f'{current_folder}_dec'] = ''
            current_ans.loc[i, f'{current_folder}_hex'] = ''
    #change column tag and merge decimal/hex
    current_ans[f'{current_folder}_dec'] = current_ans[f'{current_folder}_dec'] + '(' + current_ans[f'{current_folder}_hex'] + ')'
    current_ans = current_ans.drop(columns=[f'{current_folder}_hex'])
    current_ans.columns[0] = f'{current_folder}'
    total_ans = pd.concat([total_ans, current_ans], axis=1)

total_ans[f'{ref_name}_dec'] = total_ans[f'{ref_name}_dec'] + '(' + total_ans[f'{ref_name}_hex'] + ')'
total_ans = total_ans.drop(columns=[f'{ref_name}_hex'])
total_ans.columns[0] = f'{ref_name}'

total_ans.to_csv('all-in-one.csv')

