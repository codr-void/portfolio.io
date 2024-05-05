# Import required libraries
import sys
sys.path.append('/home/pi/MasterPi/')  # Adjust path as needed
import ArmIK

def main():
    arm = ArmIK.Arm()
    target_position = [100, 100, 20]  # Target position (x, y, z)
    angles = arm.calculate_ik(target_position)
    if angles:
        arm.move_to(angles)
    else:
        print("Position out of reach.")

if __name__ == '__main__':
    main()
