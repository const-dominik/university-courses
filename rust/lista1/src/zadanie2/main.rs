fn main() {}

fn count_red_beads(n: u32) -> u32 {
    if n < 2 {
        return 0;
    }
    return n * 2 - 2;
}

#[test]
fn beads() {
    assert_eq!(count_red_beads(0), 0);
    assert_eq!(count_red_beads(1), 0);
    assert_eq!(count_red_beads(3), 4);
    assert_eq!(count_red_beads(5), 8);
    assert_eq!(count_red_beads(7), 12);
}
