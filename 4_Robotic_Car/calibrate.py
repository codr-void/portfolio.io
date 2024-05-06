import sys
sys.path.append('/home/pi/MasterPi/')
import CameraCalibration

def calibrate_camera():
    calibrator = CameraCalibration.Calibrator()
    calibration_data = calibrator.calibrate()
    calibrator.save_calibration_data(calibration_data, 'calibration_file.yml')

if __name__ == '__main__':
    calibrate_camera()
