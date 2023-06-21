from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import os
import time
import argparse

import cv2
import numpy as np
from glob import glob

import sys

sys.path.append(os.getcwd())
from core.config import cfg

from models.rknnlite_rk3588_tracker import NnoTracker_RKNNLite

parser = argparse.ArgumentParser(description='tracking demo')

parser.add_argument('--config', default='./models/config/config.yaml', type=str, help='config file')

parser.add_argument('--save', action='store_true', help='whether visualzie result')

args = parser.parse_args()

def get_frames(video_name):
    if not video_name:
        cap = cv2.VideoCapture(0)
        # warmup
        for i in range(5):
            cap.read()
        while True:
            ret, frame = cap.read()
            if ret:
                yield frame
            else:
                break

    elif video_name.endswith('avi') or \
            video_name.endswith('mp4') or \
            video_name.endswith('mov'):
        cap = cv2.VideoCapture(video_name)

        # warmup
        for i in range(50):
            cap.read()

        while True:
            ret, frame = cap.read()
            if ret:
                yield frame
            else:
                break
    else:
        images = glob(os.path.join(video_name, '*.jp*'))
        images = sorted(images,
                        key=lambda x: int(x.split('/')[-1].split('.')[0]))
        for img in images:
            frame = cv2.imread(img)
            yield frame


def main():
    # load config
    cfg.merge_from_file(args.config)

    # load_weight
    Tback_weight = './weights/track_backbone_T.rknn'
    Xback_weight = './weights/track_backbone_X.rknn'
    Head_weight = './weights/head.rknn'

    video_name = './data/{your_video}'
    tracker = NnoTracker_RKNNLite(Tback_weight, Xback_weight, Head_weight)
    first_frame = True

    # img_savedir = './data/debug_img/'
    # count = 0

    cap = cv2.VideoCapture()
    ret,frame = cap.read()
    init_rect = [280,472,70,47]
    tracker.init(frame,init_rect)
    while(1):
        ret,frame = cap.read()
        outputs = tracker.track(frame)
        cv2.imshow("Deneme",frame)
        cv2.waitKey(1)


if __name__ == '__main__':
    main()
