use std::cmp::Ord;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::clone::Clone;
use std::marker::Copy;
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

#[derive(Copy, Clone)]
enum QSIKind {
    First,
    Last,
    MedianOf3,
}

fn quick_sort_index<T: Ord + Copy>(arr: &Vec<T>, low: usize, high: usize, pivot_type: QSIKind) -> usize {
    match pivot_type {
        QSIKind::First => low,
        QSIKind::Last => high,
        QSIKind::MedianOf3 => {
            let median: usize = (low + high) / 2;
            let mut m3arr: [(T, usize); 3] = [(arr[low], low), (arr[median], median), (arr[high], high)];
            // bubble sort
            if m3arr[0].0 < m3arr[1].0 {
                m3arr.swap(0, 1);
            }
            if m3arr[1].0 < m3arr[2].0 {
                m3arr.swap(1, 2);
            }
            if m3arr[0].0 < m3arr[1].0 {
                m3arr.swap(0, 1);
            }
            m3arr[1].1
        }
    }
}

fn quick_sort<T: Ord + Copy>(arr: &mut Vec<T>, low: Option<usize>, high: Option<usize>, pivot_type: Option<QSIKind>) -> i64 {
    let low_index: usize = low.unwrap_or(0);
    let high_index: usize = high.unwrap_or(arr.len() - 1);
    let mut comparisons: i64 = 0;

    // perform quicksort
    if high_index > low_index {
        let ptype: QSIKind = pivot_type.unwrap_or(QSIKind::First);
        let mut pivot_index: usize = quick_sort_index(arr, low_index, high_index, ptype);
        arr.swap(pivot_index, low_index);
        let pivot_value: T = arr[low_index];
        pivot_index = low_index;
        for i in (low_index + 1)..=high_index {
            comparisons += 1;
            if arr[i] < pivot_value {
                arr.swap(pivot_index + 1, i);
                pivot_index += 1;
            }
        }
        arr.swap(pivot_index, low_index);
        comparisons += quick_sort(
            arr,
            Some(low_index),
            // prevent underflow of usize type
            Some(if pivot_index == 0 { 0 } else { pivot_index - 1 }),
            Some(ptype)
        );
        comparisons += quick_sort(arr, Some(pivot_index + 1), Some(high_index), Some(ptype));
    }
    return comparisons;
}

fn main() {
    // performance timer
    let mut timer: SystemTime;

    // create number array and read in file
    println!("Reading input file...");
    timer = SystemTime::now();
    let mut arr: Vec<i32> = Vec::new();
    read_lines("QuickSort.txt".to_string(), &mut arr);
    println!("Read time: {:?}\n", timer.elapsed().unwrap());

    // sort array for problem 1
    let mut arr_copy: Vec<i32> = arr.clone();
    let mut comparisons: i64;
    println!("Sorting array using low index as pivot index...");
    timer = SystemTime::now();
    comparisons = quick_sort::<i32>(&mut arr_copy, None, None, None);
    // for v in &arr_copy {
    //     println!("{}", *v);
    // }
    println!("Sort time: {:?}\n", timer.elapsed().unwrap());
    println!("Comparisons: {}\n", comparisons);

    // sort array for problem 2
    let mut arr_copy: Vec<i32> = arr.clone();
    println!("Sorting array using last index as pivot index...");
    timer = SystemTime::now();
    comparisons = quick_sort::<i32>(&mut arr_copy, None, None, Some(QSIKind::Last));
    println!("Sort time: {:?}\n", timer.elapsed().unwrap());
    println!("Comparisons: {}\n", comparisons);

    // sort array for problem 3
    let mut arr_copy: Vec<i32> = arr.clone();
    println!("Sorting array using median of 3 index as pivot index...");
    timer = SystemTime::now();
    comparisons = quick_sort::<i32>(&mut arr_copy, None, None, Some(QSIKind::MedianOf3));
    println!("Sort time: {:?}\n", timer.elapsed().unwrap());
    println!("Comparisons: {}\n", comparisons);
}
