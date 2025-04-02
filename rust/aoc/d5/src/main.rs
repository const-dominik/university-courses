use std::{collections::HashMap, fs};

fn get_card_strength(card: char, is_2: bool) -> i32 {
    if is_2 {
        return "J23456789TQKA".chars().position(|c| c == card).unwrap() as i32 + 13;
    }
    "23456789TJQKA".chars().position(|c| c == card).unwrap() as i32
}

fn get_hand_type(hand: &str, is_2: bool) -> i32 {
    // 5, 4, 3 and 2, 3, two pairs, pair, high

    let mut card_count: HashMap<char, i32> = HashMap::new();

    for card in hand.chars() {
        let count = card_count.entry(card).or_insert(0);
        *count += 1;
    }
    let mut jokers = 0;
    if is_2 {
        if card_count.contains_key(&'J') {
            jokers = *card_count.get(&'J').unwrap();
        }
    }
    let mut card_count_vec: Vec<i32> = card_count.values().cloned().collect();
    card_count_vec.sort();

    let mut hand_type: i32;

    match card_count_vec.as_slice() {
        &[1, 1, 1, 1, 1] => hand_type = 1,
        &[1, 1, 1, 2] => hand_type = 2,
        &[1, 2, 2] => hand_type = 3,
        &[1, 1, 3] => hand_type = 4,
        &[2, 3] => hand_type = 5,
        &[1, 4] => hand_type = 6,
        &[5] => hand_type = 7,
        _ => unreachable!(),
    }

    if is_2 && jokers > 0 {
        match hand_type {
            1 => hand_type = 2,
            2 => hand_type = 4,
            3 => hand_type = 4 + jokers,
            4 => hand_type = 6,
            _ => hand_type = 7,
        }
    }
    hand_type
}

fn deck_sort_predicate(a: &str, b: &str, is_2: bool) -> std::cmp::Ordering {
    let compare_types = get_hand_type(a, is_2).cmp(&get_hand_type(b, is_2));
    if compare_types == std::cmp::Ordering::Equal {
        for i in 0..a.len() {
            let a_strength = get_card_strength(a.chars().nth(i).unwrap(), is_2);
            let b_strength = get_card_strength(b.chars().nth(i).unwrap(), is_2);

            if a_strength != b_strength {
                return a_strength.cmp(&b_strength);
            }
        }
        unreachable!()
    } else {
        return compare_types;
    }
}

fn main() {
    let input = fs::read_to_string("input.txt").unwrap();
    let lines: Vec<&str> = input.split("\n").collect();

    let mut deck: Vec<(&str, i32)> = lines
        .iter()
        .map(|line| {
            let hand: Vec<&str> = line.split_whitespace().collect();
            let number = hand[1].parse::<i32>().unwrap();

            (hand[0], number)
        })
        .collect();

    deck.sort_by(|(hand1, _bid1), (hand2, _bid2)| deck_sort_predicate(hand1, hand2, true));

    let mut sum = 0;

    for (i, (_hand, bid)) in deck.iter().enumerate() {
        sum += bid * (i as i32 + 1);
    }
    println!("{}", sum);
}
