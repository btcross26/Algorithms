use std::fs::File;
use std::io::{BufRead, BufReader};
use std::mem::replace;
use std::time::SystemTime;

fn read_lines(filename: String, arr: &mut Vec<i32>) {
    // Open the file in read-only mode.
    let file = File::open(filename).unwrap();

    // Read the file line by line and parse the ints in each line
    let lines = BufReader::new(file).lines();
    for line in lines {
        let v: &str = line.as_ref().unwrap().trim();
        arr.push(v.parse().expect("unable to parse int!"));
    }
}

#[derive(Default)]
struct MergeSortResult {
    sorted_list: Option<Vec<i32>>,
    inversions: i64,
}

fn merge(left_res: &mut MergeSortResult, right_res: &mut MergeSortResult) -> MergeSortResult {
    // Perform merge but also count inversions
    let mut left_arr: Vec<i32> = left_res.sorted_list.take().unwrap();
    let mut right_arr: Vec<i32> = right_res.sorted_list.take().unwrap();
    let mut merged_arr: Vec<i32> = Vec::new();
    let mut inversions: i64 = left_res.inversions + right_res.inversions;
    let mut i: usize = 0;
    let mut j: usize = 0;

    // perform the merge and count inversions
    loop {
        let mut v: i32;
        if left_arr[i] <= right_arr[j] {
            v = replace(&mut left_arr[i], 0);
            merged_arr.push(v);
            i += 1;
        } else {
            v = replace(&mut right_arr[j], 0);
            merged_arr.push(v);
            inversions += (left_arr.len() - i) as i64;
            j += 1;
        }

        if i == left_arr.len() as usize {
            for k in j..right_arr.len() as usize {
                v = replace(&mut right_arr[k], 0);
                merged_arr.push(v);
            }
            break;
        }

        if j == right_arr.len() as usize {
            for k in i..left_arr.len() as usize {
                v = replace(&mut left_arr[k], 0);
                merged_arr.push(v);
            }
            break;
        }
    }

    MergeSortResult {
        sorted_list: Some(merged_arr),
        inversions: inversions,
    }
}

fn merge_sort_with_inversions(arr: &[i32]) -> MergeSortResult {
    if arr.len() <= 1 {
        MergeSortResult {
            sorted_list: Some(arr.to_vec()),
            inversions: 0,
        }
    } else {
        let i: usize = (arr.len() / 2) as usize;
        let mut left_res: MergeSortResult = merge_sort_with_inversions(&arr[..i]);
        let mut right_res: MergeSortResult = merge_sort_with_inversions(&arr[i..]);
        return merge(&mut left_res, &mut right_res);
    }
}

fn main() {
    // performance timer
    let mut timer: SystemTime;

    // create number array and read in file
    println!("Reading input file...");
    timer = SystemTime::now();
    let mut arr: Vec<i32> = Vec::new();
    read_lines("IntegerArray.txt".to_string(), &mut arr);
    println!("Read time: {:?}\n", timer.elapsed().unwrap());

    // sort array
    println!("Sorting array and counting inversions...");
    timer = SystemTime::now();
    let result: MergeSortResult = merge_sort_with_inversions(&arr);
    println!("Sorting run time: {:?}", timer.elapsed().unwrap());

    // for v in result.sorted_list.as_ref().ok_or(Err(1)).unwrap() {
    //     println!("{}", *v);
    // }
    println!("Number of inversions: {:?}", result.inversions);
}
