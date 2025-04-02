use regex::Regex;
use std::fs;

fn get_number(s: &str) -> i64 {
    let re = Regex::new(r"\d+").unwrap();
    let caps = re.captures(s).unwrap();
    caps.get(0).unwrap().as_str().parse::<i64>().unwrap()
}

fn line_parser(line: &str, is_2: bool) -> i64 {
    let mut max = [("red", 0), ("green", 0), ("blue", 0)];
    let game_id = get_number(line);
    let games: Vec<&str> = line.split(";").collect();

    for game in games {
        for color in &mut max {
            let re = Regex::new(&format!(r"(\d+) {}", color.0)).unwrap();
            if let Some(caps) = re.captures(game) {
                let num = get_number(caps.get(0).unwrap().as_str());
                if num > color.1 {
                    color.1 = num;
                }
            }
        }
    }

    if is_2 {
        return max[0].1 * max[1].1 * max[2].1;
    }

    if max[0].1 > 12 || max[1].1 > 13 || max[2].1 > 14 {
        return 0;
    }

    game_id
}

fn main() {
    let input = fs::read_to_string("input.txt").unwrap();
    let lines: Vec<&str> = input.split("\n").collect();
    let mut sum: i64 = 0;
    for line in lines {
        sum += line_parser(line, true);
    }
    println!("{}", sum);
}
