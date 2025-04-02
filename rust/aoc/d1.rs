use std::fs;

fn get_number(s: String, is_2: bool) -> i64 {
    let mut first: i64 = -1;
    let mut last: i64 = 0;
    let mut line = s;

    if is_2 {
        line = line
            .replace("one", "one1one")
            .replace("two", "two2two")
            .replace("three", "three3three")
            .replace("four", "four4four")
            .replace("five", "five5five")
            .replace("six", "six6six")
            .replace("seven", "seven7seven")
            .replace("eight", "eight8eight")
            .replace("nine", "nine9nine");
    }

    for x in line.chars() {
        if x >= '0' && x <= '9' {
            if first < 0 {
                first = x as i64 - '0' as i64;
            }
            last = x as i64 - '0' as i64;
        }
    }
    std::cmp::max(first * 10 + last, 0)
}

fn main() {
    let input = fs::read_to_string("input.txt").unwrap();
    let mut sum: i64 = 0;

    for x in input.split("\n") {
        sum += get_number(x.to_string(), true);
    }

    print!("{}", sum);
}
