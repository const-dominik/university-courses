use core::str::FromStr;
use regex::Regex;
use std::fs;

#[derive(Debug)]
struct Card {
    number: u32,
    numbers_before_pipe: Vec<u32>,
    numbers_after_pipe: Vec<u32>,
}

impl FromStr for Card {
    type Err = &'static str;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let re = Regex::new(r"Card\s+(\d+):\s+((?:\d+\s*)+)\|\s+((?:\d+\s*)+)").unwrap();

        if let Some(captures) = re.captures(s) {
            let number: u32 = captures[1]
                .parse()
                .map_err(|_| "Failed to parse card number")?;
            let numbers_before_pipe: Vec<u32> = captures[2]
                .split_whitespace()
                .map(|num| {
                    num.parse()
                        .map_err(|_| "Failed to parse numbers before pipe")
                })
                .collect::<Result<Vec<u32>, &'static str>>()?;
            let numbers_after_pipe: Vec<u32> = captures[3]
                .split_whitespace()
                .map(|num| {
                    num.parse()
                        .map_err(|_| "Failed to parse numbers after pipe")
                })
                .collect::<Result<Vec<u32>, &'static str>>()?;

            Ok(Card {
                number,
                numbers_before_pipe,
                numbers_after_pipe,
            })
        } else {
            Err("Invalid input format")
        }
    }
}

fn get_card_point(card: &Card) -> u32 {
    let mut matches = 0;
    for num in &card.numbers_after_pipe {
        if card.numbers_before_pipe.contains(num) {
            matches += 1;
        }
    }

    if matches > 0 {
        return 2u32.pow(matches - 1);
    }

    0
}

fn get_final_index(card: &Card) -> u32 {
    let mut matches = 0;
    for num in &card.numbers_after_pipe {
        if card.numbers_before_pipe.contains(num) {
            matches += 1;
        }
    }

    matches + card.number
}

fn main() {
    let input = fs::read_to_string("input.txt").unwrap();
    let lines: Vec<&str> = input.split("\n").collect();
    let mut scratchcards = vec![1; lines.len()];
    let mut sum = 0;
    for line in lines {
        match line.parse::<Card>() {
            Ok(card) => {
                let is_2 = true;
                if is_2 {
                    let final_index = get_final_index(&card);
                    for i in card.number..final_index {
                        scratchcards[i as usize] += scratchcards[(card.number - 1) as usize];
                    }
                } else {
                    sum += get_card_point(&card);
                }
            }
            Err(e) => {
                eprintln!("Error: {}", e);
            }
        }
    }

    println!("Sum: {}", sum);
    print!("Total scratchcards: {}", scratchcards.iter().sum::<u32>());
}
