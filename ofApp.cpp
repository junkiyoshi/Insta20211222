#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	float deg_span = 90;
	float len = 20;

	for (float radius = len; radius < 720; radius += 36) {

		for (float deg = 0; deg < 360; deg += deg_span) {

			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto prev_noise_location = glm::vec2(cos((deg - deg_span) * DEG_TO_RAD), sin((deg - deg_span) * DEG_TO_RAD));
			auto next_noise_location = glm::vec2(cos((deg + deg_span) * DEG_TO_RAD), sin((deg + deg_span) * DEG_TO_RAD));
			
			auto noise_value = ofNoise(glm::vec3(noise_location * 0.5, radius * 0.003 + ofGetFrameNum() * 0.075));
			auto prev_noise_value = ofNoise(glm::vec3(prev_noise_location * 0.5, radius * 0.003 + ofGetFrameNum() * 0.075));
			auto next_noise_value = ofNoise(glm::vec3(next_noise_location * 0.5, radius * 0.003 + ofGetFrameNum() * 0.075));

			if (noise_value > 0.5) {

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec3((radius + len * 0.5) * cos((deg + deg_span * 0.5) * DEG_TO_RAD), (radius + len * 0.5) * sin((deg + deg_span * 0.5) * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3((radius - len * 0.5) * cos((deg + deg_span * 0.5) * DEG_TO_RAD), (radius - len * 0.5) * sin((deg + deg_span * 0.5) * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3((radius - len * 0.5) * cos((deg - deg_span * 0.5) * DEG_TO_RAD), (radius - len * 0.5) * sin((deg - deg_span * 0.5) * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3((radius + len * 0.5) * cos((deg - deg_span * 0.5) * DEG_TO_RAD), (radius + len * 0.5) * sin((deg - deg_span * 0.5) * DEG_TO_RAD), 0));

				this->face.addVertices(vertices);
				this->frame.addVertices(vertices);

				this->face.addTriangle(this->face.getNumVertices() - 1, this->face.getNumVertices() - 2, this->face.getNumVertices() - 3);
				this->face.addTriangle(this->face.getNumVertices() - 1, this->face.getNumVertices() - 3, this->face.getNumVertices() - 4);

				this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 4);
				this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 3);

				if (prev_noise_value <= 0.5) {

					this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (next_noise_value <= 0.5) {

					this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 4);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	ofRotate(ofGetFrameNum());

	ofColor color;
	color.setHsb(ofGetFrameNum() % 255, 255, 0);
	
	ofSetColor(color);
	this->face.draw();

	ofSetColor(128);
	this->frame.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}