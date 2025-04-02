fn main() {}

fn assert_close(a: f64, b: f64, epsilon: f64) {
    assert!((a - b).abs() < epsilon, "Expected: {}, got: {}", b, a);
}

fn square_area_to_circle(size: f64) -> f64 {
    let side = size.sqrt();
    let r = side / 2.0;
    return PI * r * r;
}

#[test]
fn circle() {
    assert_close(square_area_to_circle(9.0), 7.0685834705770345, 1e-8);
    assert_close(square_area_to_circle(20.0), 15.70796326794897, 1e-8);
    assert_close(square_area_to_circle(30.0), 23.56194490192345, 1e-8);
    assert_close(square_area_to_circle(40.0), 31.415926535897935, 1e-8);
    assert_close(square_area_to_circle(50.0), 39.269908169872416, 1e-8);
}
