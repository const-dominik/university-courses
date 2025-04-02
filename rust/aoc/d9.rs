use std::fs;

fn differences(sequence: &[i32]) -> Vec<i32> {
    sequence.windows(2).map(|w| w[1] - w[0]).collect()
}

fn extrapolate(sequence: &[i32], is_2: bool) -> i32 {
    if sequence.iter().all(|&x| x == 0) {
        return 0;
    }

    let diffs = differences(sequence);

    if !is_2 {
        sequence.last().unwrap() + extrapolate(&diffs, false)
    } else {
        sequence.first().unwrap() - extrapolate(&diffs, true)
    }
}

fn main() {
    let input = fs::read_to_string("input.txt").unwrap();
    let lines: Vec<&str> = input.split("\n").collect();
    let mut total = 0;
    let mut total_2 = 0;

    for line in lines {
        let sequence: Vec<i32> = line
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();

        total += extrapolate(&sequence, false);
        total_2 += extrapolate(&sequence, true);
    }

    println!("{}", total);
    println!("{}", total_2);
}
