use std::f64::consts::PI;

fn main() {}

fn assert_close(a: f64, b: f64, epsilon: f64) {
    assert!((a - b).abs() < epsilon, "Expected: {}, got: {}", b, a);
}

fn string_to_number(s: &str) -> i32 {
    return s.parse().unwrap();
}

fn count_red_beads(n: u32) -> u32 {
    if n < 2 {
        0
    } else {
        n * 2 - 2
    }
}

fn square_area_to_circle(size: f64) -> f64 {
    let side = size.sqrt();
    let r = side / 2.0;
    return PI * r * r;
}

fn printer_error(s: &str) -> String {
    let mut errors = 0;
    let all = s.len() as i32;
    for c in s.chars() {
        if (c as u32) > 109 {
            errors += 1;
        }
    }
    let ret_str = format!("{}/{}", errors, all);
    return ret_str;
}

#[test]
fn str_to_num() {
    assert_eq!(string_to_number("1234"), 1234);
    assert_eq!(string_to_number("605"), 605);
    assert_eq!(string_to_number("1405"), 1405);
    assert_eq!(string_to_number("-7"), -7);
    assert_eq!(string_to_number("-20"), -20);
}

#[test]
fn beads() {
    assert_eq!(count_red_beads(0), 0);
    assert_eq!(count_red_beads(1), 0);
    assert_eq!(count_red_beads(3), 4);
    assert_eq!(count_red_beads(5), 8);
    assert_eq!(count_red_beads(7), 12);
}

#[test]
fn circle() {
    assert_close(square_area_to_circle(9.0), 7.0685834705770345, 1e-8);
    assert_close(square_area_to_circle(20.0), 15.70796326794897, 1e-8);
    assert_close(square_area_to_circle(30.0), 23.56194490192345, 1e-8);
    assert_close(square_area_to_circle(40.0), 31.415926535897935, 1e-8);
    assert_close(square_area_to_circle(50.0), 39.269908169872416, 1e-8);
}

#[test]
fn printer() {
    assert_eq!(
        &printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"),
        "3/56"
    );
    assert_eq!(
        &printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"),
        "6/60"
    );
    assert_eq!(
        &printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"),
        "11/65"
    );
    assert_eq!(&printer_error("abcdeeffg"), "0/9");
    assert_eq!(&printer_error("n"), "1/1");
}
