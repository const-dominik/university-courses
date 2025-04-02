use regex::Regex;
use std::fs;
use std::str::FromStr;

#[derive(Debug)]
struct TimeDistance {
    time_values: Vec<i64>,
    distance_values: Vec<i64>,
}

impl FromStr for TimeDistance {
    type Err = &'static str;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let re = Regex::new(
            r"Time:\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+Distance:\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)",
        )
        .unwrap();

        if let Some(captures) = re.captures(s) {
            let time_values: Vec<i64> = (1..=4)
                .map(|i| {
                    captures[i]
                        .parse()
                        .map_err(|_| "Failed to parse time values")
                })
                .collect::<Result<Vec<i64>, &'static str>>()?;
            let distance_values: Vec<i64> = (5..=8)
                .map(|i| {
                    captures[i]
                        .parse()
                        .map_err(|_| "Failed to parse distance values")
                })
                .collect::<Result<Vec<i64>, &'static str>>()?;

            Ok(TimeDistance {
                time_values,
                distance_values,
            })
        } else {
            Err("Invalid input format")
        }
    }
}

fn calc_ways(max_time: i64, max_dist: i64) -> i64 {
    // p - push time
    // d - race distance
    // t - race time
    // we need to calculate how many p solves p(t-p) > d

    let delta = max_time * max_time - 4 * (max_dist + 1);
    let sqrt_delta = (delta as f64).sqrt();

    let x1 = ((max_time as f64 - sqrt_delta) / 2.0).ceil() as i64;
    let x2 = ((max_time as f64 + sqrt_delta) / 2.0).floor() as i64;

    println!("x1: {}, x2: {}", x1, x2);
    x2 - x1 + 1
}

fn main() {
    let input = fs::read_to_string("input.txt").unwrap();
    let mut res = 1;

    match input.parse::<TimeDistance>() {
        Ok(td) => {
            println!("{:?}", td);
            for i in 0..4 {
                res = res * calc_ways(td.time_values[i], td.distance_values[i])
            }
        }
        Err(e) => {
            eprintln!("Error: {}", e);
        }
    }
    println!("Result: {}", res);
    println!("Result_2: {}", calc_ways(41777096, 249136211271011));
}
